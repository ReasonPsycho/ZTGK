//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_UNIT_H
#define ZTGK_UNIT_H
#include "ECS/Grid/Grid.h"
#include "Utils/AstarPathfinding.h"


struct UnitStats{
    float health;
    float attackDamage;
    float attackSpeed;
    float movementSpeed;
    float range;
};



class Unit {
public:
    UnitStats stats;
    Vector2Int gridPosition;



private:
    Grid* grid;
    AstarPathfinding pathfinding;
};


#endif //ZTGK_UNIT_H
