//
// Created by igork on 25.03.2024.
//

#ifndef MOP_H
#define MOP_H
#include "ECS/Unit/Equipment/Item.h"


class Mop : public Item{
public:
    Mop() : Item("Mop", "A mop to clean the floor", true, ItemStats(10, 1, GridRange(1, 0)), false) {
        icon_path = "res/textures/icons/item_mop.png";
    }
};



#endif //MOP_H
