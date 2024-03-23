//
// Created by igork on 22.03.2024.
//

#include "CombatState.h"

State *CombatState::RunCurrentState() {
    //from Combat to Idle
    if (!unit->hasMovementTarget && !unit->hasCombatTarget && !unit->hasMiningTarget) {
        return IdleState;
    }

    //from Combat to Movement
    if (unit->hasMovementTarget) {
        return MoveState;
    }

    //from Combat to Mining
    if (!unit->hasMovementTarget && !unit->hasCombatTarget && unit->hasMiningTarget && unit->isTargetInRange) {
        return MiningState;
    }

    return this;
}