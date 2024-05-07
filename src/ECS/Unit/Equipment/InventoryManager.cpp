//
// Created by cheily on 06.05.2024.
//

#include "InventoryManager.h"
#include "ECS/Unit/Unit.h"
#include "ECS/Unit/Equipment/ConcreteItems/Mop.h"
#include "ECS/Unit/Equipment/ConcreteItems/WaterGun.h"
#include "ECS/Unit/Equipment/ConcreteItems/Hands.h"

InventoryManager * InventoryManager::instance = nullptr;

void InventoryManager::init() {
    instance = this;

    item_constructors.emplace(Item::item_types.hands, [](){ return new Hands(); });
    item_constructors.emplace(Item::item_types.mop, [](){ return new Mop(); });
    item_constructors.emplace(Item::item_types.water_gun, [](){ return new WaterGun(); });
}

Item *InventoryManager::create_item(unsigned int type_id) {
    auto item = std::unique_ptr<Item>(item_constructors[type_id]());
    auto ret = item.get();
    free_items.push_back(std::move(item));
    return ret;
}

Item *InventoryManager::create_default_item(Unit *unit) {
    auto item = std::unique_ptr<Item>(item_constructors[Item::item_types.hands]());
    auto ret = item.get();
    unit->equipment.item0 = ret;
    assigned_items.push_back(std::move(item));

    return ret;
}

void InventoryManager::delete_item(Item *item) {
    auto it = get_item(item->uniqueID);
    if (it.first == nullptr)
        return;

    if (it.second)
        std::erase(assigned_items, std::unique_ptr<Item>(it.first));
    else std::erase(free_items, std::unique_ptr<Item>(it.first));
}

std::pair<Item *, bool> InventoryManager::get_item(unsigned int item_uid) {
    auto found = std::find_if(free_items.begin(), free_items.end(), [item_uid](auto & item){
        return item->uniqueID == item_uid;
    });
    if (found != free_items.end())
        return {(*found).get(), false};

    found = std::find_if(assigned_items.begin(), assigned_items.end(), [item_uid](auto & item){
        return item->uniqueID == item_uid;
    });
    if (found != assigned_items.end())
        return {(*found).get(), true};

    return {nullptr, false};
}

bool InventoryManager::assign_item(Item *item, Unit *unit, short slot) {
    if (!mv_to_asgn(item)) {
        spdlog::error("Item not found or not freed before! Cannot assign!");
        return false;
    }
    
    auto un_eq = unit->equipment.equipItem(item, slot);
    // equipItem() automatically unequips the other items for use,
    //  so we just need to move them to the right collection
    if (un_eq.first)
        mv_to_free(un_eq.first);
    if (un_eq.second)
        mv_to_free(un_eq.second);

    unit->UpdateStats();
    return true;
}

bool InventoryManager::unassign_item(Unit *unit, Item *item) {
    if (unit->equipment.item1 == item) {
        return unassign_item(unit, 1);
    } else if (unit->equipment.item2 == item) {
        return unassign_item(unit, 2);
    }
    return false;
}

bool InventoryManager::unassign_item(Unit *unit, short slot) {
    return unit->equipment.unequipItem(slot);
}

void InventoryManager::spawn_item_on_map(Item *item, glm::vec2 world_pos) {
    spdlog::debug("InventoryManager::spawn_item_on_map is TODO");
}

void InventoryManager::showImGuiDetailsImpl(Camera *camera) {
    Component::showImGuiDetailsImpl(camera);
}

bool InventoryManager::mv_to_free(Item * item) {
    auto found = std::find_if(free_items.begin(), free_items.end(), [item](auto & elem){
        return elem->uniqueID == item->uniqueID;
    });
    if (found == free_items.end()) {
        return false;
    }
    // SO 5792703
    auto new_elem = std::move(*found);
    free_items.erase(found);
    assigned_items.push_back(std::move(new_elem));

    return true;
}

bool InventoryManager::mv_to_asgn(Item * item) {
    auto found = std::find_if(assigned_items.begin(), assigned_items.end(), [item](auto & elem){
        return elem->uniqueID == item->uniqueID;
    });
    if (found == assigned_items.end()) {
        return false;
    }
    // SO 5792703
    auto new_elem = std::move(*found);
    assigned_items.erase(found);
    free_items.push_back(std::move(new_elem));

    return true;
}

InventoryManager::InventoryManager() { name = "Inventory Manager"; }
