//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_UNIT_H
#define ZTGK_UNIT_H
#include "ECS/Grid/Grid.h"
#include "Utils/AstarPathfinding.h"
#include "UnitAI/StateMachine/StateManager.h"

struct UnitStats{
    float health;
    float attackDamage;
    float attackSpeed;
    float movementSpeed;
    float range;
};

enum TargetType{
    NONE,
    ENEMY,
    MINING,
    GROUND
};


class Unit {
public:
    UnitStats stats;
    Vector2Int gridPosition;
    TargetType targetType;
    State* currentState;



private:
    Grid* grid;
    AstarPathfinding pathfinding;

};


#endif //ZTGK_UNIT_H
