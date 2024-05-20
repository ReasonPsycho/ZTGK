//
// Created by cheily on 08.04.2024.
//
#include "Group.h"
#include "imgui.h"
#include "ECS/Utils/Util.h"
#include "spdlog/spdlog.h"
#include "glm/gtc/type_ptr.hpp"
#include "ECS/SignalQueue/SignalQueue.h"
#include "ECS/SignalQueue/DataCargo/EditorSignals/HUD/HUDRemoveGroupSignalData.h"
#include "ECS/SignalQueue/DataCargo/EditorSignals/HUD/HUDSortZDepthSignalData.h"

using namespace ztgk;

Group::Group() : id(::id<ID_POOL_HUD_GROUP>()), hidden(false), offset(0, 0, 0) {}

Group::Group(/* ignored */ unsigned int id) : id(0), hidden(false), offset(0, 0, 0)
{}

Group Group::default_group() {
    auto ret = Group(0);
    ret.name = "Root";
    ret.parent = static_cast<unsigned>(-1);
    return ret;
}

bool Group::isHidden() const {
    return hidden;
}

void Group::setHidden(bool hidden) {
    this->hidden = hidden;
    // perhaps play fadeout or slide animation here
}

void Group::imgui_controls() {
    if (id == 0) ImGui::Text("%s", std::format("Group {} - {}", id, name).c_str());
    else         ImGui::Text("%s", std::format("Group {} - {} : parent {}", id, name, parent).c_str());

    ImGui::SameLine();
    if (ImGui::SmallButton(std::format("Toggle hide: {}##{}", hidden, id).c_str()))
        setHidden(!hidden);
    if ( id != 0 ) {
        ImGui::SameLine();
        if (ImGui::SmallButton(std::format("Remove Group##{}", id).c_str())) {
            *ztgk::game::scene->systemManager.getSystem<SignalQueue>()
                    += HUDRemoveGroupSignalData::signal(id,"Editor event");
        }
    }
    static float prevz;
    prevz = offset.z;
    ImGui::DragFloat3(std::format("Offset##{}", id).c_str(), glm::value_ptr(offset));
    if ( prevz != offset.z ) {
        *ztgk::game::scene->systemManager.getSystem<SignalQueue>()
                += HUDSortZDepthSignalData::signal("Editor event.");
    }
    if (id != 0) {
        if (ImGui::TreeNode(std::format("Config##{}", id).c_str())) {
            ImGui::InputInt(std::format("Parent##{}", id).c_str(), reinterpret_cast<int *>(&parent));
            static char *name_buf = new char[50];
            strcpy_s(name_buf, 50, name.c_str());
            ImGui::InputText(std::format("Name##{}", id).c_str(), name_buf, 50);
            name = name_buf;
            ImGui::TreePop();
        }
    }
}
