//
// Created by cheily on 13.05.2024.
//

#include "MineableChest.h"
#include "ECS/Unit/Equipment/Item.h"
#include "ECS/Unit/Equipment/InventoryManager.h"


void MineableChest::showImGuiDetailsImpl(Camera *camera) {
    ImGui::Text("Item Type: %d", item_type_id);
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("%s", Item::item_types.types_string().c_str());
    IMineable::showImGuiDetailsImpl(camera);
}

void MineableChest::onMined(Unit *unit) {
    IMineable::onMined(unit);
    auto item = InventoryManager::instance->create_item(item_type_id);
    auto pos = grid->GridToWorldPosition(gridPosition);
    InventoryManager::instance->spawn_item_on_map(item, {pos.x, pos.z});
}
