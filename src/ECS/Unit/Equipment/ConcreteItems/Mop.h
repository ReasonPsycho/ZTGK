//
// Created by igork on 25.03.2024.
//

#ifndef MOP_H
#define MOP_H
#include "ECS/Unit/Equipment/Item.h"


class Mop : public Item{
public:
    Mop() : Item("Mop", "A mop to clean the floor", ItemStats(0, 10, 5, 0, 1), false) {}
};



#endif //MOP_H
