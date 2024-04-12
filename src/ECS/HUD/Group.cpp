//
// Created by cheily on 08.04.2024.
//
#include "Group.h"
#include "imgui.h"
#include "Utils/Util.h"
#include "glm/gtc/type_ptr.hpp"
#include "ECS/SignalQueue/SignalQueue.h"
#include "ECS/SignalQueue/DataCargo/EditorSignals/HUD/HUDRemoveGroupSignalData.h"
#include "ECS/SignalQueue/DataCargo/EditorSignals/HUD/HUDSortZDepthSignalData.h"

using namespace ztgk;

Group::Group() : id(::id<ID_POOL_HUD_GROUP>()), hidden(false), offset(0, 0, 0) {}

Group::Group(/* ignored */ unsigned int id) : id(0), hidden(false), offset(0, 0, 0)
{}

Group Group::default_group() {
    return Group(0);
}

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
    if ( id != 0 ) {
        ImGui::SameLine();
        if (ImGui::SmallButton(std::format("Remove Group##{}", id).c_str())) {
            *ztgk::game::scene->systemManager.getSystem<SignalQueue>()
                    += HUDRemoveGroupSignalData::signal(id,"Editor event");
        }
        // no id input because groups are a map, so it doesn't really update anything, vector would work
//        ImGui::SameLine();
//        ImGui::InputInt(std::format("ID##{}", id).c_str(), reinterpret_cast<int *>(&id));
//        if (ImGui::IsItemHovered())
//            ImGui::SetTooltip("Obviously dangerous. Don't make duplicates, only fill in for deleted groups.");
    }
    static float prevz;
    prevz = offset.z;
    ImGui::DragFloat3(std::format("Offset##{}", id).c_str(), glm::value_ptr(offset));
    if ( prevz != offset.z ) {
        *ztgk::game::scene->systemManager.getSystem<SignalQueue>()
                += HUDSortZDepthSignalData::signal("Editor event.");
    }
}
