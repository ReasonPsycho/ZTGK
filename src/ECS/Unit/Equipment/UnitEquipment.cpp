//
// Created by igork on 25.03.2024.
//

#include "UnitEquipment.h"

#include <iostream>

UnitEquipment::UnitEquipment() {
    // todo item0 =
    item1 = nullptr;
    item2 = nullptr;
}

bool UnitEquipment::equipItem(Item* item, short slot) {
    if(slot == 1 || slot == 2){
        if(item->takesTwoSlots) {
            if(item1 != nullptr) {
                unequipItem(1);
            }
            if(item2 != nullptr) {
                unequipItem(2);
            }
            item1 = item;
            return true;
        }
        if(slot==1){
            if(item1 != nullptr) {
                unequipItem(1);
            }
            item1 = item;
            return true;
        }if(slot == 2){
            if(item2 != nullptr) {
                unequipItem(2);
            }
            item2 = item;
            return true;
        }
    }
    else{
        std::cerr << "Invalid slot. Trying to equip item into "<<slot<< ". slot, while unit has only 2." << std::endl;
        return false;
    }
}

Item* UnitEquipment::unequipItem(short slot) {
    if (slot == 1) {
        Item* temp = item1;
        item1 = nullptr;
        return temp;
    }if(slot == 2){
        Item* temp = item2;
        item2 = nullptr;
        return temp;
    }
    std::cerr << "Invalid slot. Trying to unequip item from "<<slot<< ". slot, while unit has only 2." << std::endl;
    return nullptr;
}

Item *UnitEquipment::in_range_of(glm::ivec2 self, glm::ivec2 target) const {
    Item * it;
    Item * sec_it = nullptr;
    Item * ret = nullptr;

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
                it = item1; sec_it = item2;
            } else {
                it = item2; sec_it = item1;
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

bool UnitEquipment::use_default() const  {
    return (item1 != nullptr && item1->offensive) || (item2 != nullptr && item2->offensive);
}