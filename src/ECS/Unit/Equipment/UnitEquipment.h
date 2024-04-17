//
// Created by igork on 25.03.2024.
//

#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "Item.h"


class UnitEquipment {
public:
    Item* item1;
    Item* item2;

    UnitEquipment();

    bool equipItem(Item* item, short slot);

    Item* unequipItem(short slot);

};



#endif //EQUIPMENT_H
