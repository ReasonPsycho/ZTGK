//
// Created by igork on 25.03.2024.
//

#ifndef WATERGUN_H
#define WATERGUN_H
#include "Equipment/Item.h"


class WaterGun : public Item{
public:
    WaterGun() : Item("Water Gun", "A water gun to clean the floor", ItemStats(0, 10, 2, 0, 3), true) {}

};



#endif //WATERGUN_H
