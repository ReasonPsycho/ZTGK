#ifndef ZTGK_UNIT_H
#define ZTGK_UNIT_H
#include "ECS/Grid/Grid.h"
#include "ECS/Entity.h"
#include "Equipment/UnitEquipment.h"
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

    Vector2Int gridPosition;
    Vector3 worldPosition;

    State* currentState;
    AstarPathfinding pathfinding;
    Grid* grid;

    UnitEquipment equipment;

    //target flags
    bool hasMovementTarget = false;
    bool hasCombatTarget = false;
    bool hasMiningTarget = false;
    bool isTargetInRange = false;

    //targets
    Vector2Int movementTarget;
    Unit* combatTarget;
    IMineable* miningTarget;
    UnitStats stats;

    Unit(Scene *scene, std::string name, Grid *grid, Vector2Int gridPosition, UnitStats stats, bool isAlly);
    ~Unit();

    bool IsAlly() const;

    void EquipItem(Item item, short slot);
    void UnequipItem(short slot);
    void UpdateStats();

    UnitStats GetBaseStats();

private:
    bool isAlly;

    UnitStats baseStats;
};


#endif //ZTGK_UNIT_H
