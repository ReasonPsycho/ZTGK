#ifndef ZTGK_UNIT_H
#define ZTGK_UNIT_H
#include "ECS/Grid/Grid.h"
#include "ECS/Entity.h"
#include "Mining/IMineable.h"
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

    //target flags
    bool hasMovementTarget = false;
    bool hasCombatTarget = false;
    bool hasMiningTarget = false;
    bool isTargetInRange = false;

    //targets
    Vector2Int movementTarget;
    Unit* combatTarget;
    IMineable* miningTarget;

    Unit(Scene *scene, std::string name, Grid *grid, Vector2Int gridPosition, UnitStats stats, bool isAlly);
    ~Unit();

    bool IsAlly() const;

private:
    bool isAlly;

};


#endif //ZTGK_UNIT_H
