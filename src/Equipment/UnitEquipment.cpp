//
// Created by igork on 25.03.2024.
//

#include "UnitEquipment.h"

#include <iostream>

UnitEquipment::UnitEquipment() {
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
