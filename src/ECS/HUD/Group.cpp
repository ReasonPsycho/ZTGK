//
// Created by cheily on 08.04.2024.
//
#include "Group.h"
#include "imgui.h"
#include "Utils/Util.h"

using namespace ztgk;

Group::Group() : id(::id<ID_POOL_CANVAS>()), hidden(false), offset(0, 0) {}

bool Group::isHidden() const {
    return hidden;
}

void Group::setHidden(bool hidden) {
    this->hidden = hidden;
    // perhaps play fadeout or slide animation here
}

void Group::imgui_controls() {
    ImGui::LabelText(std::format("Group {}", id).c_str(), "");
    ImGui::DragFloat2("Offset", (float *) &offset);
}
