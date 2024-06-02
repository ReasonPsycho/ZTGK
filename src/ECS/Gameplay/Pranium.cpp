//
// Created by igork on 23.05.2024.
//

#include "Pranium.h"
#include "ECS/Render/Components/Render.h"
#include "ECS/Entity.h"
#include "ECS/Utils/Globals.h"
#include "ECS/Unit/Equipment/InventoryManager.h"
#include "ECS/Unit/Equipment/ConcreteItems/PraniumOre.h"

Pranium::Pranium(float timeToMine, Vector2Int gridPosition, Grid *grid) : IMineable(timeToMine, gridPosition, grid) {
    name = "Pranium";

}

void Pranium::onMine(Unit *unit) {

}

void Pranium::onMined(Unit *unit) {
    auto item = InventoryManager::instance->create_item(Item::item_types.pranium_ore);
    InventoryManager::instance->spawn_item_on_map(item, VectorUtils::Vector2IntToGlmVec2(gridPosition));

    auto tile = getEntity()->getComponent<Tile>();
    tile->state = TileState::FLOOR;
    tile->getEntity()->removeComponentFromMap(tile->getEntity()->getComponent<Render>());
//    tile->getEntity()->removeComponentFromMap(this);

}

void Pranium::generatePranium(Model *model) {
    auto parent = getEntity();
    auto render = parent->getComponent<Render>();
    if(render != nullptr){
        parent->removeComponentFromMap(render);
    }
    parent->addComponent(std::make_unique<Render>(model));


}
