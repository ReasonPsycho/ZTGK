//
// Created by cheily on 08.04.2024.
//
#include "Group.h"
#include "imgui.h"
#include "Utils/Util.h"
#include "spdlog/spdlog.h"
#include "glm/gtc/type_ptr.hpp"

using namespace ztgk;

Group::Group() : id(::id<ID_POOL_HUD_GROUP>()), hidden(false), offset(0, 0, 0) {}

bool Group::isHidden() const {
    return hidden;
}

void Group::setHidden(bool hidden) {
    this->hidden = hidden;
    // perhaps play fadeout or slide animation here
}

void Group::imgui_controls() {
    ImGui::Text("%s", std::format("Group {}", id).c_str());
    ImGui::SameLine();
    if (ImGui::SmallButton(std::format("Toggle hide: {}##{}", hidden, id).c_str()))
        setHidden(!hidden);
    ImGui::SameLine();
    if (ImGui::SmallButton(std::format("Remove Group##{}", id).c_str())) {
        spdlog::info("Todo Make this send signal to HUD.");
        // todo send signal
    }
    ImGui::DragFloat3(std::format("Offset##{}", id).c_str(), glm::value_ptr(offset));
}
