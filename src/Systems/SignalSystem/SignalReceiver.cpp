//
// Created by cheily on 20.03.2024.
//

#include "SignalReceiver.h"
#include "Systems/Util.h"
#include "Camera.h"
#include "imgui_impl_opengl3.h"

using namespace ztgk_util;

SignalReceiver::SignalReceiver() : SignalReceiver(0, [](const Signal&){}) {}

SignalReceiver::SignalReceiver(unsigned int receiveTypeMask, std::function<void(const Signal&)> onSignal)
        : uid(id<ID_POOL_COMPONENT>()), receive_type_mask(receiveTypeMask), receive(onSignal) {}

void SignalReceiver::showImGuiDetails(Camera *camera) {
    ImGui::PushID(uniqueID);
    if (ImGui::TreeNode("Signal Receiver")) {
        ImGui::TreePop();
    }
    ImGui::PopID();
}
