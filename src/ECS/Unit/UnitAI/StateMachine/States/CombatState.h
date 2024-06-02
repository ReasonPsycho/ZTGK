#ifndef COMBATSTATE_H
#define COMBATSTATE_H

#include "ECS/Unit/UnitAI/StateMachine/State.h"
#include "ECS/Unit/Equipment/Item.h"
#include <memory>

class CombatState : public State {
public:
    // Constructor
    CombatState(Grid* grid, Unit* unit);

    // Static method to get the instance of CombatState
    static std::unique_ptr<CombatState> getInstance(Grid* grid, Unit* unit);

    // Methods
    std::unique_ptr<State> RunCurrentState() override;
    bool isTargetInRange() override;

    Item* useItem;

private:
    void AttackTarget();
    bool isAttackOnCooldown();

    // Static member to hold the singleton instance
    static std::unique_ptr<CombatState> instance;
};

#endif // COMBATSTATE_H
