#ifndef ZTGK_UNIT_H
#define ZTGK_UNIT_H
#include "ECS/Grid/Grid.h"
#include "ECS/Entity.h"
#include "ECS/Unit/Equipment/UnitEquipment.h"
#include "ECS/Unit/Mining/IMineable.h"
#include "ECS/Utils/AstarPathfinding.h"
#include "ECS/Unit/UnitAI/StateMachine/StateManager.h"

struct UnitStats{
    float health;
    float attackDamage;
    float attackSpeed;
    float movementSpeed;
    float range;
};


class Unit : public Component {
public:

    bool isSelected = false;

    Vector2Int gridPosition;
    glm::vec3 worldPosition;

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

    Unit(std::string name, Grid *grid, Vector2Int gridPosition, UnitStats stats, bool isAlly);
    ~Unit();

    bool IsAlly() const;

    void EquipItem(Item item, short slot);
    void UnequipItem(short slot);
    void UpdateStats();

    UnitStats GetBaseStats();

    void showImGuiDetails(Camera *camera) override;
    void Update() override;

private:
    bool isAlly;

    UnitStats baseStats;
};


#endif //ZTGK_UNIT_H
