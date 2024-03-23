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

std::unordered_map<unsigned, std::pair<SignalReceiver*, std::vector<std::string>>> SignalReceiver::debugClones{};

SignalReceiver::SignalReceiver() : SignalReceiver(0, [](const Signal&){}) {}

SignalReceiver::SignalReceiver(unsigned int receiveTypeMask, std::function<void(const Signal&)> onSignal)
        : uid(id<ID_POOL_COMPONENT>()), receive_type_mask(receiveTypeMask), receive(onSignal) {}

void SignalReceiver::showImGuiDetails(Camera *camera) {
    ImGui::PushID(uniqueID);
    if (ImGui::TreeNode("Signal Receiver")) {
        ImGui::Text("ID: %d", uid);
        ImGui::Text("Types: %d", receive_type_mask);
        ImGui::Text("Has callback: %d", bool(receive));

        if (ImGui::Button("Subscribe debug clone")) {
            if (debugClones.contains(uid)) {
                (this->parentEntity->systemManager->getSystem<SignalQueue>())->post(Signal(
                    0,
                    0,
                    debugClones[uid].first->uid,
                    [](){},
                    "Debug print clone already exists!"
                ));
                ImGui::SetWindowFocus(std::format("Debug print of receiver {}({})", uid, receive_type_mask).c_str());
            } else {
                auto clone = new SignalReceiver(*this);
                clone->uid = id<ID_POOL_COMPONENT>();   // id needs to be unique, otherwise we'll remove the original when unsubscribing
                clone->receive = [original = this](const Signal &signal) {
                    debugClones[original->uid].second.push_back(std::format(
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
            ImGui::End();
        }
        ImGui::TreePop();
    }
    ImGui::PopID();
}
