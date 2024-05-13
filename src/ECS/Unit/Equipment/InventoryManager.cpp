//
// Created by cheily on 06.05.2024.
//

#include "InventoryManager.h"
#include "ECS/Unit/Unit.h"
#include "ECS/Unit/UnitSystem.h"
#include "ECS/Unit/Equipment/ConcreteItems/Mop.h"
#include "ECS/Unit/Equipment/ConcreteItems/WaterGun.h"
#include "ECS/Unit/Equipment/ConcreteItems/Hands.h"
#include "ECS/Unit/Equipment/ConcreteItems/TestBuffItem.h"

InventoryManager * InventoryManager::instance = nullptr;

void InventoryManager::init() {
    instance = this;

    item_constructors.emplace(Item::item_types.hands, [](){ return new Hands(); });
    item_constructors.emplace(Item::item_types.mop, [](){ return new Mop(); });
    item_constructors.emplace(Item::item_types.water_gun, [](){ return new WaterGun(); });
    item_constructors.emplace(Item::item_types.test_buff_item, [](){ return new TestBuffItem(); });
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
    delete_item(item->uniqueID);
}

void InventoryManager::delete_item(unsigned int item_id) {
    auto it = get_item(item_id);
    if (it.first == nullptr) {
        spdlog::error("Trying to delete item that was not found within the inventory system!");
        return;
    }

    if (it.second) {
        spdlog::warn("Deleting assigned item without unequiping!");
        std::erase_if(assigned_items, [item = it.first](auto & elem){ return elem->uniqueID == item->uniqueID; });
    }
    else std::erase_if(free_items, [item = it.first](auto & elem){ return elem->uniqueID == item->uniqueID; });
    ztgk::game::scene->stopRenderingImgui = true;
}

void InventoryManager::unassign_and_delete_item(Unit *unit, short slot) {
    auto item = unit->equipment[slot];
    if (!unassign_item(unit, slot))
        return;
    delete_item(item);
}

void InventoryManager::unassign_and_delete_item(Unit *unit, Item *item) {
    if (item == unit->equipment[1])
        unassign_and_delete_item(unit, 1);
    else if (item == unit->equipment[2])
        unassign_and_delete_item(unit, 2);
    else if (item == unit->equipment[0]) {
        spdlog::warn("Unequipping default item!!");
        unassign_and_delete_item(unit, (short)0);
    }
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
    auto item = unit->equipment[slot];
    if (item == nullptr) {
        spdlog::error("Trying to free null item! Incorrect slot or slot empty.");
        return false;
    }
    if (!mv_to_free(item)) {
        spdlog::error("Cannot free item! Could have possibly freed or incorrectly assigned before!");
        return false;
    }
    unit->equipment.unequipItem(slot);
    unit->UpdateStats();
    return true;
}

void InventoryManager::spawn_item_on_map(Item *item, glm::vec2 world_pos) {
    spdlog::debug("InventoryManager::spawn_item_on_map is TODO");
}

void InventoryManager::showImGuiDetailsImpl(Camera *camera) {
    if (ImGui::CollapsingHeader("Controls")) {
        static int item_type_id = 0;
        static int item_id = 0;
        static int unit_id = 0;
        static int unit_slot = 1;
        static bool trigger_unequip = true;
        static bool new_item = false;
        static bool e_delete_item = false;
        static Item * found = nullptr;
        static Unit * found_unit = nullptr;
        static bool found_assigned = false;

        if (ImGui::TreeNode("Create Item")) {
            ImGui::InputInt("Type ID", &item_type_id);
            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("%s", Item::item_types.types_string().c_str());
            }
            if (ImGui::Button("Create"))
                create_item(item_type_id);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Find Item")) {
            ImGui::InputInt("Item ID", &item_id);
            if (ImGui::Button("Search")) {
                std::tie(found, found_assigned) = get_item(item_id);
                if (found) {
                    auto units = ztgk::game::scene->systemManager.getSystem<UnitSystem>()->unitComponents;
                    auto unit = std::find_if(units.begin(), units.end(), [](Unit * unit){
                        return unit->equipment.has(found);
                    });
                    if (unit == units.end())
                        found_unit = nullptr;
                    else
                        found_unit = *unit;
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Clear")) {
                found = nullptr;
                found_unit = nullptr;
                found_assigned = false;
            }
            if (found) {
                ImGui::Text("Item is %s", (found_assigned ? "assigned" : "unassigned"));
                if (ImGui::TreeNode(std::format("{1} - id {0}", found->uniqueID, found->name).c_str())) {
                    found->imgui_preview();
                    ImGui::TreePop();
                }
                if (found_unit) {
                    if (ImGui::TreeNode(std::format("{1} - id {0}", found_unit->uniqueID, found_unit->name).c_str())) {
                        found_unit->showImGuiDetailsImpl(ztgk::game::camera);
                        ImGui::TreePop();
                    }
                }
            }
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Delete Item")) {
            ImGui::InputInt("Item ID", &item_id);
            ImGui::Checkbox("Trigger unequip effect?", &trigger_unequip);
            if (trigger_unequip) {
                ImGui::InputInt("Unit ID", &unit_id);
            }
            if (ImGui::Button("Delete")) {
                if (trigger_unequip) {
                    auto units = ztgk::game::scene->systemManager.getSystem<UnitSystem>()->unitComponents;
                    auto unit = std::find_if(units.begin(), units.end(), [](Unit * unit){ return unit->uniqueID == unit_id; });
                    if (unit == units.end()) {
                        spdlog::error("Unit not found!");
                    } else {
                        unassign_and_delete_item(*unit, get_item(item_id).first);
                    }
                } else {
                    delete_item(item_id);
                }
                found = nullptr;
                found_unit = nullptr;
                found_assigned = false;
            }
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Assign Item")) {
            ImGui::Checkbox("Create Item?", &new_item);
            if (new_item) {
                ImGui::InputInt("Type ID", &item_type_id);
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("%s", Item::item_types.types_string().c_str());
                }
            }
            else {
                ImGui::InputInt("Item ID", &item_id);
            }
            ImGui::InputInt("Unit ID", &unit_id);
            ImGui::InputInt("Unit eq slot", &unit_slot);

            if (ImGui::Button("Assign")) {
                auto units = ztgk::game::scene->systemManager.getSystem<UnitSystem>()->unitComponents;
                auto unit = std::find_if(units.begin(), units.end(), [](Unit * unit){ return unit->uniqueID == unit_id; });
                if (unit == units.end()) {
                    spdlog::error("Unit not found!");
                } else {
                    if (new_item) {
                        auto item = create_item(item_id);
                        assign_item(item, *unit, unit_slot);
                    } else {
                        auto item = get_item(item_id);
                        if (!item.first) {
                            spdlog::error("Couldn't find item to be assigned!");
                        } else {
                            assign_item(item.first, *unit, unit_slot);
                        }
                    }
                }

            }
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Unassign Item")) {
            ImGui::InputInt("Unit ID", &unit_id);
            ImGui::InputInt("Unit eq slot", &unit_slot);
            ImGui::Checkbox("Delete Item?", &e_delete_item);
            if (ImGui::Button("Unassign")) {
                auto units = ztgk::game::scene->systemManager.getSystem<UnitSystem>()->unitComponents;
                auto unit = std::find_if(units.begin(), units.end(), [](Unit * unit){ return unit->uniqueID == unit_id; });
                if (unit == units.end()) {
                    spdlog::error("Unit not found!");
                } else {
                    if (e_delete_item)
                        unassign_and_delete_item(*unit, unit_slot);
                    else unassign_item(*unit, unit_slot);
                }
            }
            ImGui::TreePop();
        }
    }
    if (ImGui::CollapsingHeader("Free Items")) {
        for (auto & item : free_items) {
            if (ImGui::TreeNode(std::format("{1} - id {0}", item->uniqueID, item->name).c_str())) {
                item->imgui_preview();
                ImGui::TreePop();
            }
        }
    }
    if (ImGui::CollapsingHeader("Assigned Items")) {
        for (auto & item : assigned_items) {
            if (ImGui::TreeNode(std::format("{1} - id {0}", item->uniqueID, item->name).c_str())) {
                item->imgui_preview();
                ImGui::TreePop();
            }
        }
    }
}

bool InventoryManager::mv_to_free(Item * item) {
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

bool InventoryManager::mv_to_asgn(Item * item) {
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

InventoryManager::InventoryManager() { name = "Inventory Manager"; }