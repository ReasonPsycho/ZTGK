// 
// Created by igork on 25.03.2024. 
// 
 
#include "UnitEquipment.h" 
#include "InventoryManager.h" 
 
#include <iostream> 
 
UnitEquipment::UnitEquipment(Unit * unit) : unit(unit) { 
    InventoryManager::instance->create_default_item(unit); 
    item1 = nullptr; 
    item2 = nullptr; 
} 
 
std::pair<Item *, Item *> UnitEquipment::equipItem(Item *item, short slot) { 
    std::pair<Item *, Item *> ret = {}; 
    if (slot == 0) { 
        spdlog::warn("Equipping into default slot!"); 
        if (item0 != nullptr) 
            ret.first = item0; 
        item0 = item; 
        return ret; 
    } 
    // any free, otherwise slot 1 
    if (slot == -1) { 
        if (item->takesTwoSlots) { 
        } else if (item1 != nullptr && item2 != nullptr) { 
            slot = 1; 
        } else if (item1 == nullptr) { 
            item1 = item; 
            return ret; 
        } else if (item2 == nullptr) { 
            item2 = item; 
            return ret; 
        } 
    } 
    if (item->takesTwoSlots) { 
        if (item1 != nullptr) { 
            ret.first = unequipItem(1); 
        } 
        if (item2 != nullptr) { 
            if (ret.first == nullptr) 
                ret.first = unequipItem(2); 
            else ret.second = unequipItem(2); 
        } 
        item1 = item; 
        return ret; 
    } 
    if (slot == 1) { 
        if (item1 != nullptr) 
            ret.first = unequipItem(1); 
        item1 = item; 
        return ret; 
    } else if (slot == 2) { 
        if (item2 != nullptr) 
            ret.first = unequipItem(2); 
        item2 = item; 
        return ret; 
    } else { 
        spdlog::error("Invalid slot. Trying to equip item into {}. slot, while unit has only 2.", slot); 
        return ret; 
    } 
} 
 
Item * UnitEquipment::unequipItem(short slot) { 
    if (slot == 1) { 
        Item *temp = item1; 
        item1 = nullptr; 
        return temp; 
    } 
    if (slot == 2) { 
        Item *temp = item2; 
        item2 = nullptr; 
        return temp; 
    } 
    spdlog::error("Invalid slot. Trying to unequip item from {}. slot, while unit has only 2.", slot); 
    return nullptr; 
} 
 
Item *UnitEquipment::in_range_of(glm::ivec2 self, glm::ivec2 target) const { 
    Item *it; 
    Item *sec_it = nullptr; 
    Item *ret = nullptr; 
 
    if (use_default()) { 
        it = item0; 
        // if not use_default() then at least one item is not null and is offensive 
    } else if (item1 == nullptr) 
        it = item2; 
    else if (item2 == nullptr) 
        it = item1; 
    else { 
        if (item1->offensive && item2->offensive) { 
            // try item with shorter range first 
            if (item1->stats.range.add <= item2->stats.range.add) { 
                it = item1; 
                sec_it = item2; 
            } else { 
                it = item2; 
                sec_it = item1; 
            } 
        } else { 
            it = item1->offensive ? item1 : item2; 
        } 
    } 
 
    auto ind = it->stats.range.get_indices(self); 
    ret = it; 
 
    // not in range of first item and there is no second item 
    if (ind.empty() && sec_it == nullptr) 
        return nullptr; 
 
    // not in range of first item 
    if (ind.empty()) { 
        ind = sec_it->stats.range.get_indices(self); 
        ret = sec_it; 
    } 
 
    // not in range of second item 
    if (ind.empty()) { 
        ret = nullptr; 
    } 
 
    return ret; 
} 
 
bool UnitEquipment::use_default() const { 
    return (item1 == nullptr && item2 == nullptr) || (item1 != nullptr && item2 != nullptr && !item1->offensive && !item2->offensive) 
            || (item1 == nullptr && item2 != nullptr && !item2->offensive) || (item1 != nullptr && item2 == nullptr && !item1->offensive); 
 
} 
 
void UnitEquipment::imgui_preview() const { 
    ImGui::Text("CD between items: %f / %f", cd_between_sec, cd_between_max_sec); 
     
    if (ImGui::TreeNode(std::format("Default : {} - id {}", item0->name, item0->uniqueID).c_str())) { 
        ImGui::Text("Cached effective range:"); 
        ImGui::SameLine(); 
        rangeEff0.imgui_preview(); 
         
        item0->imgui_preview(); 
        ImGui::TreePop(); 
    } 
     
    if (ImGui::TreeNode(std::format("Item 1 : {} - id {}", item1 == nullptr ? "none" : item1->name.c_str(), item1 == nullptr ? 0 : item1->uniqueID).c_str())) { 
        if (item1 != nullptr) { 
            ImGui::Text("Cached effective range:"); 
            ImGui::SameLine(); 
            rangeEff1.imgui_preview(); 
 
            item1->imgui_preview(); 
        } 
        ImGui::TreePop(); 
    } 
     
    if (ImGui::TreeNode(std::format("Item 2 : {} - id {}", item2 == nullptr ? "none" : item2->name.c_str(), item2 == nullptr ? 0 : item2->uniqueID).c_str())) { 
        if (item2 != nullptr) { 
            ImGui::Text("Cached effective range:"); 
            ImGui::SameLine(); 
            rangeEff2.imgui_preview(); 
 
 
            item2->imgui_preview(); 
        } 
        ImGui::TreePop(); 
    } 
     
} 
 
bool UnitEquipment::is_full() const { 
    return item1 && item2; 
} 
