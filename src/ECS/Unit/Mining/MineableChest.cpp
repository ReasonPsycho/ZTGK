//
// Created by cheily on 13.05.2024.
//

#include "MineableChest.h"
#include "ECS/Unit/Equipment/Item.h"
#include "ECS/Unit/Equipment/InventoryManager.h"
#include "ECS/Entity.h"
#include "ECS/Unit/Mining/MiningSystem.h"


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

void MineableChest::UpdateImpl() {
//    auto tile = grid->getTileAt(gridPosition);
//    auto render = getEntity()->getComponent<Render>();
//    if(tile == nullptr || render == nullptr) return;
//    render->isInFogOfWar = tile->isInFogOfWar;
}

MineableChest::MineableChest(const Vector2Int &gridPosition, Grid *grid, unsigned int itemTypeId) : IMineable(timeToMine, gridPosition, grid) {
    this->name = "MineableChest";
    this->gridPosition = gridPosition;
    this->grid = grid;
    this->item_type_id = itemTypeId;
    this->timeToMine = 5;
    this->timeToMineRemaining = timeToMine;
    //ztgk::game::scene->systemManager.getSystem<MiningSystem>()->addComponent(this);

}

MineableChest::~MineableChest() {
    ztgk::game::scene->systemManager.getSystem<MiningSystem>()->removeComponent(this);
}
