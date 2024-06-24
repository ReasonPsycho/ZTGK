//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_COMBATSTATE_H
#define ZTGK_COMBATSTATE_H

#include "ECS/Unit/UnitAI/StateMachine/State.h"
#include "ECS/Unit/Equipment/Item.h"
class MovementState;
class MiningState;
class IdleState;

class CombatState : public State{
public:
    CombatState(Grid* grid);

    State* RunCurrentState() override;
    bool isTargetInRange() override;

    MovementState *moveState;
    MiningState* miningState;
    IdleState* idleState;

    Item * useItem;

    bool isAttackOnCooldown();
    static void applyDamage(Unit* unit, Unit* target, float dmg);

    void AttackTarget();
    // spaghetti way of exposing attack logic without forcing target checks, for active non-offensive items without rewriting the logic
    static void AttackSideFX(Item * useItem, Unit * unit, Unit * target);
};


#endif //ZTGK_COMBATSTATE_H
