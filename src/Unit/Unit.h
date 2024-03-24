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


class Unit : public Entity {
public:
    UnitStats stats;
    Vector2Int gridPosition;
    Vector3 worldPosition;

    State* currentState;
    AstarPathfinding pathfinding;
    Grid* grid;

    bool hasMovementTarget = false;
    bool hasCombatTarget = false;
    bool hasMiningTarget = false;
    bool isTargetInRange = false;

    Vector2Int target;

    Unit(SystemManager *systemManager, std::string name, Grid *grid, Vector2Int gridPosition);


private:


};


#endif //ZTGK_UNIT_H
