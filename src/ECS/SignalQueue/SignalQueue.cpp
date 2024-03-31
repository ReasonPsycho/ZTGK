//

#include "SignalQueue.h"
#include "ECS/Util.h"
#include "imgui.h"
#include "DataCargo/KeySignalData.h"
#include "DataCargo/AudioSignalData.h"
#include "DataCargo/TestSignalData.h"
#include "DataCargo/MouseEvents/MouseButtonSignalData.h"
#include "DataCargo/MouseEvents/MouseScrollSignalData.h"
#include "DataCargo/MouseEvents/MouseMoveSignalData.h"

using namespace ztgk;
//
// Created by cheily on 20.03.2024.
void SignalQueue::init() {
    update_delta();
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

void SignalQueue::showImGuiDetails(Camera *camera) {
    auto &cfg = editor_new_signal_config;

    if (ImGui::CollapsingHeader("Queue control")){

        ImGui::Text("dt: %lld", get_delta());
        if (ImGui::Button("Toggle log")) {
            cfg.enablelog = !cfg.enablelog;

            if (cfg.enablelog) {
                cfg.logger = editor_s_new_signal_config::new_logger();
                *this += cfg.logger;
            } else {
                *this -= cfg.logger;
                cfg.log.clear();
                delete cfg.logger;
            }
        }
        if (cfg.enablelog) {
            ImGui::SameLine();
            if (ImGui::Button("Print")) {
                cfg.log.emplace_back("Current queue:");
                for (const auto &item: queue)
                    cfg.log.push_back("\t" + item.to_string());
            }
            ImGui::SameLine();
            if (ImGui::Button("Clear"))
                cfg.log.clear();

            cfg.logger->showImGuiDetails(nullptr);
        }

        ImGui::Text("New Signal:");
        if (ImGui::Button("Post")) {
            std::shared_ptr<SignalData> data;
            auto choicemask = 1 << cfg.choice;
            if (choicemask == Signal::signal_types.test_signal) {
                data = std::make_shared<TestSignalData>(cfg.message);
            } else if (choicemask == Signal::signal_types.keyboard_signal) {
                data = std::make_shared<KeySignalData>(cfg.key, cfg.scancode, cfg.kaction, cfg.kmods, cfg.message);
            } else if (choicemask == Signal::signal_types.mouse_button_signal) {
                data = std::make_shared<MouseButtonSignalData>(cfg.button, cfg.maction, cfg.mmods, cfg.message);
            } else if (choicemask == Signal::signal_types.mouse_move_signal) {
                data = std::make_shared<MouseMoveSignalData>(Vec2{cfg.xnew, cfg.ynew}, Vec2{cfg.xold, cfg.yold},
                                                             cfg.message);
            } else if (choicemask == Signal::signal_types.mouse_scroll_signal) {
                data = std::make_shared<MouseScrollSignalData>(Vec2{cfg.xoff, cfg.yoff}, cfg.message);
            } else if (choicemask == Signal::signal_types.audio_signal) {
                data = std::make_shared<AudioSignalData>(cfg.soundpath, cfg.message);
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
        const char *types[] = {"Test", "Keyboard", "Mouse Button", "Mouse Move", "Mouse Scroll", "Audio"};
        ImGui::Combo("Type", &cfg.choice, types, 6);
        unsigned choicemask = 1 << cfg.choice;

        if (choicemask == Signal::signal_types.test_signal) {
        } else if (choicemask == Signal::signal_types.keyboard_signal) {
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
        } else {
            ImGui::Text("Unimplemented - see SignalQueue::editor_control_window");
        }
    }
    
    if (cfg.enablelog) {
        if(ImGui::CollapsingHeader("Queue log")){
            for (auto &line: cfg.log) {
                ImGui::Text("%s", line.c_str());
            }
            if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.0f); 
        }
    }
}

SignalQueue::SignalQueue() {
name = "Signal Queue";
}

SignalReceiver *SignalQueue::editor_s_new_signal_config::new_logger() {
    return new SignalReceiver(
            Signal::signal_types.all,
            [](const Signal &signal) {
                editor_new_signal_config.log.emplace_back(std::format(
                        "[{}] received signal {}",
                        ztgk::time(), signal.to_string()
                ).c_str());
            });
}
