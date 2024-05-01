#include "SignalQueue.h"
#include "ECS/Utils/Util.h"
#include "imgui.h"
#include "DataCargo/KeySignalData.h"
#include "DataCargo/AudioSignalData.h"
#include "DataCargo/TestSignalData.h"
#include "DataCargo/MouseEvents/MouseButtonSignalData.h"
#include "DataCargo/MouseEvents/MouseScrollSignalData.h"
#include "DataCargo/MouseEvents/MouseMoveSignalData.h"
#include "DataCargo/EditorSignals/HUD/HUDRemapGroupsSignalData.h"
#include "DataCargo/EditorSignals/HUD/HUDSortZDepthSignalData.h"
#include "DataCargo/EditorSignals/HUD/HUDRemoveGroupSignalData.h"

using namespace ztgk;
void SignalQueue::init() {
    update_delta();

    editor_log.console = std::make_unique<Console>("Signal Queue");
    editor_log.recv = std::make_unique<SignalReceiver>( editor_s_logging::new_receiver() );
    editor_log.console->custom_menus = {
        {
            "Print Q",
            [this](){
                editor_log.console->log("Current queue:");
                for (const auto &item: queue)
                    editor_log.console->log("\t" + item.to_string());
            }
        },
    };
}

long long SignalQueue::get_delta() {
    return ztgk::time() - timestamp;
}

long long SignalQueue::update_delta() {
    auto t = timestamp;
    timestamp = ztgk::time();
    return timestamp - t;
}

void SignalQueue::process_one(long long deltatime) {
    auto signal = queue.front();
    queue.pop_front();
    signal.time_to_live -= deltatime;
    if (signal.time_to_live > 0) {
        queue.push_back(signal);
        return;
    }

    auto filtered = receivers | std::views::filter([signal](SignalReceiver *receiver) {
        if (signal.receiver_id != 0)
            return signal.receiver_id == receiver->receiver_uid;
        else return (signal.stype & receiver->receive_type_mask) != 0;
    });

    for (auto &receiver: filtered) {
        receiver->receive(signal);
        if (signal.consume) break;
    }

    if (signal.callback) signal.callback();
}

void SignalQueue::process_all() {
    auto delta = update_delta();

    for (int i = 0; i < queue.size(); ++i) {
        process_one(delta);
    }
}

void SignalQueue::post(const Signal &signal) {
    queue.push_back(signal);
}

void SignalQueue::cancel(unsigned int signalId) {
    std::erase_if(queue, [signalId](const Signal &signal) { return signal.sid == signalId; });
}

std::vector<Signal> SignalQueue::peek(unsigned int signal_type) {
    auto filtered = queue | std::ranges::views::filter([signal_type](const Signal &signal) {
        return signal_type == 0 || signal.stype == signal_type;
    });
    std::vector<Signal> ret;
    std::copy(filtered.begin(), filtered.end(), ret.begin());
    return ret;
}

SignalQueue &SignalQueue::operator+=(const Signal &signal) {
    post(signal);
    return *this;
}

SignalQueue &SignalQueue::operator-=(const Signal &signal) {
    cancel(signal.sid);
    return *this;
}

SignalQueue &SignalQueue::operator+=(SignalReceiver *receiver) {
    receivers.push_back(receiver);
    return *this;
}

SignalQueue &SignalQueue::operator-=(SignalReceiver *receiver) {
    std::erase(receivers, receiver);
    return *this;
}

void SignalQueue::addComponent(void *component) {
    receivers.push_back((SignalReceiver *) component);
}

// editor
SignalQueue::editor_s_new_signal_config SignalQueue::editor_new_signal_config{};
SignalQueue::editor_s_logging SignalQueue::editor_log{};

void SignalQueue::showImGuiDetailsImpl(Camera *camera) {
    auto &cfg = editor_new_signal_config;
    auto &log = editor_log;

    if (ImGui::Button("Toggle log")) {
        log.enable = !log.enable;

        if (log.enable) {
            *this += log.recv.get();
        } else {
            *this -= log.recv.get();
        }
    }
    ImGui::SameLine();
    ImGui::Text("dt: %lld", get_delta());
    if ( log.enable && ImGui::TreeNodeEx(std::format("Debug Receiver##{}", log.recv->receiver_uid).c_str(), ImGuiTreeNodeFlags_SpanAvailWidth) ) {
        log.recv->showImGuiDetailsImpl(camera);
        ImGui::TreePop();
    }

    if (ImGui::CollapsingHeader("Signal Spoofing")){
        if (ImGui::Button("Post")) {
            std::shared_ptr<SignalData> data;
            auto choicemask = 1 << cfg.choice;
            if (choicemask == Signal::signal_types.test) {
                data = std::make_shared<TestSignalData>(cfg.message);
            } else if (choicemask == Signal::signal_types.keyboard) {
                data = std::make_shared<KeySignalData>(cfg.key, cfg.scancode, cfg.kaction, cfg.kmods, cfg.message);
            } else if (choicemask == Signal::signal_types.mouse_button_signal) {
                data = std::make_shared<MouseButtonSignalData>(cfg.button, cfg.maction, cfg.mmods, cfg.message);
            } else if (choicemask == Signal::signal_types.mouse_move_signal) {
                data = std::make_shared<MouseMoveSignalData>(Vec2{cfg.xnew, cfg.ynew}, Vec2{cfg.xold, cfg.yold},
                                                             cfg.message);
            } else if (choicemask == Signal::signal_types.mouse_scroll_signal) {
                data = std::make_shared<MouseScrollSignalData>(glm::vec2{cfg.xoff, cfg.yoff}, cfg.message);
            } else if (choicemask == Signal::signal_types.audio_signal) {
                data = std::make_shared<AudioSignalData>(cfg.soundpath, cfg.message);
            } else if (choicemask == Signal::signal_types.hud_sort_z_depth_signal) {
                data = std::make_shared<HUDSortZDepthSignalData>(cfg.message);
            } else if (choicemask == Signal::signal_types.hud_update_group_mappings_signal) {
                data = std::make_shared<HUDRemapGroupsSignalData>(cfg.all, cfg.componentID, (hudcType)cfg.componentType, cfg.oldGroupID, cfg.newGroupID, cfg.message);
            } else if (choicemask == Signal::signal_types.hud_remove_group_signal) {
                data = std::make_shared<HUDRemoveGroupSignalData>(cfg.groupId, cfg.message);
            } else {
                data = std::make_shared<SignalData>(cfg.message);
            }

            for (int i = 0; i < cfg.nsignals; ++i) {
                auto sig = Signal{
                        static_cast<unsigned int>(1 << cfg.choice),
                        static_cast<long long>(cfg.defertime * 1000),
                        cfg.receiver,
                        data,
                        nullptr
                };
                sig.consume = cfg.consume;
                post(sig);
            }

        }
        ImGui::InputFloat("Defer time (sec)", &cfg.defertime);
        ImGui::InputText("Message", cfg.message, editor_s_new_signal_config::message_size);

        ImGui::InputInt("Amount to send", &cfg.nsignals);
        ImGui::InputInt("Receiver ID", reinterpret_cast<int *>(&cfg.receiver));
        ImGui::Checkbox("Single-use", &cfg.consume);
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(
                    "The signal will be consumed after the first receiver handles it (unless it explicitly sets the flag otherwise)."
                    "\nThat is the first event in order of subscription that matches the typemask or id."
                    "\nThis also means any log will only print this signal if no other receiver caught it.");
        }
        static const char *types[] = {"Test", "Keyboard", "Audio", "Mouse Button", "Mouse Move", "Mouse Scroll", "Hud UpdateImpl mappings", "Hud sort z depth", "Hud remove group"};
        ImGui::Combo("Type", &cfg.choice, types, 9);
        // assumes types are ordered the same way type id masks are initialized!!
        unsigned choicemask = 1 << cfg.choice;

        if (choicemask == Signal::signal_types.test) {
        } else if (choicemask == Signal::signal_types.keyboard) {
            ImGui::InputInt("Key", &cfg.key);
            ImGui::InputInt("Scancode", &cfg.scancode);
            ImGui::InputInt("Action", &cfg.kaction);
            ImGui::InputInt("Mods", &cfg.kmods);
        } else if (choicemask == Signal::signal_types.mouse_button_signal) {
            ImGui::InputInt("Button", &cfg.button);
            ImGui::InputInt("Action", &cfg.maction);
            ImGui::InputInt("Mods", &cfg.mmods);
        } else if (choicemask == Signal::signal_types.mouse_move_signal) {
            ImGui::InputDouble("New X", &cfg.xnew);
            ImGui::InputDouble("New Y", &cfg.ynew);
            ImGui::InputDouble("Old X", &cfg.xold);
            ImGui::InputDouble("Old Y", &cfg.yold);
        } else if (choicemask == Signal::signal_types.mouse_scroll_signal) {
            ImGui::InputDouble("X-offset", &cfg.xoff);
            ImGui::InputDouble("Y-offset", &cfg.yoff);
        } else if (choicemask == Signal::signal_types.audio_signal) {
            ImGui::InputText("Sound filepath", cfg.soundpath, editor_s_new_signal_config::message_size);
        } else if (choicemask == Signal::signal_types.hud_update_group_mappings_signal) {
            ImGui::Checkbox("All?", &cfg.all);
            if ( !cfg.all ) {
                ImGui::InputInt("Component ID", &cfg.componentID);
                static const char *componentTypeLabels[] = {"UNDEFINED", "TEXT", "SPRITE"};
                ImGui::Combo("Component Type", &cfg.componentType, componentTypeLabels, 3);
                ImGui::InputInt("Old Group ID", &cfg.oldGroupID);
                ImGui::InputInt("New Group ID", &cfg.newGroupID);
            }
        } else if (choicemask == Signal::signal_types.hud_sort_z_depth_signal) {
            ImGui::Text("No unique fields.");
        } else if (choicemask == Signal::signal_types.hud_remove_group_signal) {
            ImGui::InputInt("Group ID", &cfg.groupId);
        } else {
            ImGui::Text("Unimplemented - see SignalQueue::editor_control_window");
        }
    }
    if ( ImGui::CollapsingHeader("Managed Components") ) {
        for (auto & recv : receivers) {
            if (ImGui::TreeNodeEx(std::format("ID {0}, RID {1}, Mask {2}##Recv{0}", recv->uniqueID, recv->receiver_uid, recv->receive_type_mask).c_str(), ImGuiTreeNodeFlags_SpanAvailWidth)) {
                recv->showImGuiDetailsImpl(camera);
                ImGui::TreePop();
            }
        }
    }

    // todo replace
    if (log.enable)
        log.console->imguiWindow();
//    if (cfg.enablelog) {
//        ImGui::Begin("Queue log");
//
//        for (auto &line: cfg.log) {
//            ImGui::Text("%s", line.c_str());
//        }
//        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
//            ImGui::SetScrollHereY(1.0f);
//
//        ImGui::End();
//    }
}

SignalQueue::SignalQueue() {
    name = "Signal Queue";
}

void SignalQueue::removeComponent(void *component) {
    receivers.erase(std::remove(receivers.begin(), receivers.end(),reinterpret_cast<SignalReceiver *const>(component)), receivers.end());
}

void SignalQueue::UpdateImpl() {
    process_all();
}

SignalReceiver SignalQueue::editor_s_logging::new_receiver() {
    return SignalReceiver(
            Signal::signal_types.all,
            [](const Signal &signal) {
                editor_log.console->log(std::format(
                        "[{}] received signal {}",
                        ztgk::time(), signal.to_string()
                ));
            });
}