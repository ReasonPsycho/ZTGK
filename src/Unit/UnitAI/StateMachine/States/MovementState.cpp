//
// Created by igork on 22.03.2024.
//

#include "MovementState.h"
#include "Unit/Unit.h"
#include "Unit/UnitAI/StateMachine/States/CombatState.h"
#include "Unit/UnitAI/StateMachine/States/IdleState.h"
#include "Unit/UnitAI/StateMachine/States/MiningState.h"


State *MovementState::RunCurrentState() {
    //from Movement to Idle
    if (!unit->hasMovementTarget && !unit->hasCombatTarget && !unit->hasMiningTarget) {
        return IdleState;
    }

    //from Movement to Combat
    if (!unit->hasMovementTarget && unit->hasCombatTarget && unit->isTargetInRange) {
        return CombatState;
    }

    //from Movement to Mining
    if (!unit->hasMovementTarget && !unit->hasCombatTarget && unit->hasMiningTarget && unit->isTargetInRange) {
        return MiningState;
    }

    return this;
}