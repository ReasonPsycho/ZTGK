//
// Created by igork on 25.03.2024.
//

#include "Item.h"
#include "ECS/Utils/Util.h"

const s_item_types Item::item_types{};

Item::Item(std::string name, std::string description, bool offensive, ItemStats stats, bool takesTwoSlots)
    : uniqueID(ztgk::id<ztgk::ID_POOL_ITEM>()), name(name), description(description), offensive(offensive), stats(stats), takesTwoSlots(takesTwoSlots) {
}

void Item::imgui_preview() const {
    ImGui::Text("Description: %s", description.c_str());
    ImGui::Text("Offensive?: %d", offensive);
    ImGui::Text("2 slot?: %d", takesTwoSlots);
    ImGui::Text("CD (sec): %f / %f", cd_sec, stats.cd_max_sec);

    ImGui::Text("Raw Stats:");
    ImGui::Indent();
        ImGui::Text("Damage: %f", stats.dmg);
        ImGui::Text("CD max (sec): %f", stats.cd_max_sec);
        stats.range.imgui_preview();
    ImGui::Unindent();

    ImGui::Text("Raw Modifiers:");
    ImGui::Indent();
        stats.add_to_unit.imgui_preview();
    ImGui::Unindent();
}
