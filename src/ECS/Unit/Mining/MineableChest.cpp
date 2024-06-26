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

// todo fix item swaps
void MineableChest::onMined(Unit *unit) {
    IMineable::onMined(unit);
    if (parentEntity->getComponent<Render>())
        parentEntity->getComponent<Render>()->Remove();
    parentEntity->addComponent(std::make_unique<Render>(ztgk::game::chestModel));
    auto item = InventoryManager::instance->create_item(item_type_id);
    InventoryManager::instance->assign_item(item, unit, -1);
    auto itemEntity = getEntity()->getChild("ItemChild");
    if(itemEntity != nullptr){
        auto itemRender = itemEntity->getComponent<Render>();
        if(itemRender != nullptr)
            itemRender->Remove();
        itemEntity->Destroy();
    }



    //To prevent unit from walking on empty hanger vvvv
    grid->getTileAt(gridPosition)->setTileState(CHEST);
    spdlog::debug("Mined chest");
}

void MineableChest::UpdateImpl() {
//  IF U CAN SEE CHESTS IN FOG OF WAR THEN UNCOMMENT THIS XOXO

    auto tile = grid->getTileAt(gridPosition);
    auto render = getEntity()->getComponent<Render>();
    if(tile == nullptr || render == nullptr) return;
    render->isInFogOfWar = tile->isInFogOfWar;
    auto itemEntity = getEntity()->getChild("ItemChild");
    if(itemEntity != nullptr){
        auto itemRender = itemEntity->getComponent<Render>();
        if(itemRender != nullptr)
            itemRender->isInFogOfWar = tile->isInFogOfWar;
    }
}

MineableChest::MineableChest(const Vector2Int &gridPosition, Grid *grid, unsigned int itemTypeId) : IMineable(timeToMine, gridPosition, grid) {
    this->name = "MineableChest";
    this->gridPosition = gridPosition;
    this->grid = grid;
    this->item_type_id = itemTypeId;
    this->timeToMine = 0.1f;
    this->timeToMineRemaining = timeToMine;
    //ztgk::game::scene->systemManager.getSystem<MiningSystem>()->addComponent(this);

}

MineableChest::~MineableChest() {
    ztgk::game::scene->systemManager.getSystem<MiningSystem>()->removeComponent(this);
}
