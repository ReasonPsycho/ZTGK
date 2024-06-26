//
// Created by cheily on 13.05.2024.
//

#include "MineableChest.h"
#include "ECS/Unit/Equipment/Item.h"
#include "ECS/Unit/Equipment/InventoryManager.h"
#include "ECS/Entity.h"
#include "ECS/Unit/Mining/MiningSystem.h"
#include "ECS/Unit/Unit.h"


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
    auto item = InventoryManager::instance->create_item(item_type_id);
    auto drop = InventoryManager::instance->assign_item(item, unit, -1);

    auto itemEntity = getEntity()->getChild("ItemChild");
    if(itemEntity != nullptr){
        auto itemRender = itemEntity->getComponent<Render>();
        if(itemRender != nullptr)
            itemRender->Remove();
        itemEntity->Destroy();
    }

    Vector2Int spawn_origin = gridPosition;
//    Item * putOnHanger = nullptr;
//    Item * putOnGround = nullptr;

    Vector2Int first_pos = unit->pathfinding.GetNearestVacantTileAround(spawn_origin, {spawn_origin});
    if (drop.first)
        InventoryManager::instance->spawn_item_on_map(drop.first, first_pos);
    if (drop.second)
        InventoryManager::instance->spawn_item_on_map(
                drop.second,
                unit->pathfinding.GetNearestVacantTileAround(spawn_origin,drop.first ? std::vector{spawn_origin,first_pos} : std::vector{spawn_origin}));

    // todo if starczy czasu..
//    if (drop.first && Item::item_types.id_of(drop.first) != Item::item_types.pranium_ore) {
//        putOnHanger = drop.first;
//    } else if (drop.first && Item::item_types.id_of(drop.first) == Item::item_types.pranium_ore) {
//        putOnGround = drop.first;
//    }
//
//    if (drop.second && Item::item_types.id_of(drop.second) != Item::item_types.pranium_ore) {
//        if (!putOnHanger) {
//            putOnHanger = drop.second;
//        } else {
//            putOnGround = drop.second;
//        }
//    } else if (drop.second && Item::item_types.id_of(drop.second) == Item::item_types.pranium_ore) {
//        putOnGround = drop.second;
//    }
//
//    if (putOnHanger) {
//        grid->MakeHangerComponents(parentEntity, Item::item_types.id_of(putOnHanger));
//        InventoryManager::instance->delete_item(putOnHanger);
//        this->isMined = false;
////        this->timeToMineRemaining = timeToMine;
//
//    }
//    if (putOnGround) {
//        InventoryManager::instance->spawn_item_on_map(putOnGround,
//                                                      unit->pathfinding.GetNearestVacantTileAround(spawn_origin,
//                                                                                                   {spawn_origin}));
//    }
//
//    if (!putOnHanger && !putOnGround)
        parentEntity->addComponent(std::make_unique<Render>(ztgk::game::chestModel));

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
