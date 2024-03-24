//
// Created by cheily on 20.03.2024.
//

#include "SignalReceiver.h"
#include "Systems/Util.h"
#include "Camera.h"
#include "imgui_impl_opengl3.h"
#include "SignalQueue.h"
#include "ECS/Entity.h"

using namespace ztgk_util;

std::unordered_map<unsigned, std::pair<SignalReceiver *, std::vector<std::string>>> SignalReceiver::debugClones{};

SignalReceiver::SignalReceiver() : SignalReceiver(0, [](const Signal &) {}) {}

SignalReceiver::SignalReceiver(unsigned int receiveTypeMask, std::function<void(const Signal & signal)> onSignal)
        : uid(id<ID_POOL_COMPONENT>()), receive_type_mask(receiveTypeMask), receive(onSignal) {}

void SignalReceiver::showImGuiDetails(Camera *camera) {

    ImGui::PushID(uniqueID);
    if (ImGui::TreeNode("Signal Receiver")) {
        ImGui::Text("UID: ");
        ImGui::SameLine(); ImGui::InputInt("", reinterpret_cast<int *>(&uid));
        ImGui::Text("Typemask: %d", receive_type_mask);
        ImGui::Text("Has callback: %d", bool(receive));
        ImGui::Text("Has parent entity: %d", bool(parentEntity));
        if (ImGui::CollapsingHeader("Typemask Config")) {
            ImGui::CheckboxFlags("Test", &receive_type_mask, Signal::signal_types.test_signal);
            ImGui::CheckboxFlags("Key", &receive_type_mask, Signal::signal_types.keyboard_signal);
            ImGui::CheckboxFlags("Mouse button", &receive_type_mask, Signal::signal_types.mouse_button_signal);
            ImGui::CheckboxFlags("Mouse move", &receive_type_mask, Signal::signal_types.mouse_move_signal);
            ImGui::CheckboxFlags("Scroll", &receive_type_mask, Signal::signal_types.mouse_scroll_signal);
            ImGui::CheckboxFlags("Audio", &receive_type_mask, Signal::signal_types.audio_signal);
            ImGui::CheckboxFlags("All", &receive_type_mask, Signal::signal_types.all);
        }

        // These controls access the parent entity in order to obtain the scene's signal queue, as the receiver itself has no information about the queue it subscribes.
        // The signal queue is required to subscribe a clone receiver, constructed with the same parameters as this receiver, that will print
        if (parentEntity != nullptr) {
            if (ImGui::Button("Subscribe debug clone")) {
                if (debugClones.contains(uid)) {
                    (this->parentEntity->systemManager->getSystem<SignalQueue>())->post(Signal(
                            0,
                            0,
                            debugClones[uid].first->uid,
                            std::make_shared<SignalData>("Debug print clone already exists!"),
                            []() {}
                    ));
                    ImGui::SetWindowFocus(
                            std::format("Debug print of receiver {}({})", uid, receive_type_mask).c_str());
                } else {
                    auto clone = new SignalReceiver(*this);
                    clone->receive = [oguid = uid](const Signal &signal) {
                        debugClones[oguid].second.push_back(std::format(
                                "[{}] received signal {}",
                                ztgk_util::time(), signal.to_string()
                        ));
                    };

                    debugClones[uid] = std::make_pair(
                            clone, std::vector<std::string>()
                    );
                    *(this->parentEntity->systemManager->getSystem<SignalQueue>()) += clone;
                }
            }
            if (ImGui::Button("Remove debug clones")) {
                *(this->parentEntity->systemManager->getSystem<SignalQueue>()) -= debugClones[uid].first;
                delete debugClones[uid].first;
                debugClones.erase(uid);
            }

            if (debugClones.contains(uid)) {
                ImGui::Begin(std::format("Debug print of receiver {}({})", uid, receive_type_mask).c_str());
                for (const auto &log_line: debugClones[uid].second)
                    ImGui::Text("%s", log_line.c_str());
                if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                    ImGui::SetScrollHereY(1.0f);
                ImGui::End();
            }
        }
        ImGui::TreePop();
    }
    ImGui::PopID();
}

void SignalReceiver::editor_typemask_config(unsigned int *mask) {
    if (ImGui::CollapsingHeader("Typemask Config")) {
        ImGui::CheckboxFlags("Test", mask, Signal::signal_types.test_signal);
        ImGui::CheckboxFlags("Key", mask, Signal::signal_types.keyboard_signal);
        ImGui::CheckboxFlags("Mouse button", mask, Signal::signal_types.mouse_button_signal);
        ImGui::CheckboxFlags("Mouse move", mask, Signal::signal_types.mouse_move_signal);
        ImGui::CheckboxFlags("Scroll", mask, Signal::signal_types.mouse_scroll_signal);
        ImGui::CheckboxFlags("Audio", mask, Signal::signal_types.audio_signal);
        ImGui::CheckboxFlags("All", mask, Signal::signal_types.all);
    }
}


