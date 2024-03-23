//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_UNIT_H
#define ZTGK_UNIT_H
#include "ECS/Grid/Grid.h"
#include "Utils/AstarPathfinding.h"
#include "UnitAI/StateMachine/StateManager.h"
#include "ECS/Component.h"

struct UnitStats{
    float health;
    float attackDamage;
    float attackSpeed;
    float movementSpeed;
    float range;
};


class Unit : public Entity {
public:
    UnitStats stats{};
    Vector2Int gridPosition{};
    State* currentState{};

    bool hasMovementTarget = false;
    bool hasCombatTarget = false;
    bool hasMiningTarget = false;
    bool isTargetInRange = false;


    Unit(SystemManager *systemManager, std::string name, Grid *grid, Vector2Int gridPosition);


private:
    Grid* grid;
    AstarPathfinding pathfinding;
};


#endif //ZTGK_UNIT_H
