//
// Created by igork on 25.03.2024.
//

#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "Item.h"


class UnitEquipment {
public:
    Unit * unit;

    // default, no item
    Item* item0;
    GridRange rangeEff0;
    [[nodiscard]] bool use_default() const;

    Item* item1;
    GridRange rangeEff1;

    Item* item2;
    GridRange rangeEff2;

    float cd_between_max_sec = 0.5;
    float cd_between_sec = 0;

    explicit UnitEquipment(Unit * unit);

    // purely for ptr management, do not use outside of InventoryManager
    std::pair<Item *, Item *> equipItem(Item* item, short slot);
    // purely for ptr management, do not use outside of InventoryManager
    Item * unequipItem(short slot);

    [[nodiscard]] Item * in_range_of(glm::ivec2 self, glm::ivec2 target) const;

    // serializer
    UnitEquipment() {};
};



#endif //EQUIPMENT_H
