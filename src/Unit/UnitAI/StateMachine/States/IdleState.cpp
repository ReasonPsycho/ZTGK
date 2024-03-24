//
// Created by igork on 22.03.2024.
//

#include "IdleState.h"
#include "Unit/Unit.h"
#include "Unit/UnitAI/StateMachine/States/MovementState.h"
#include "Unit/UnitAI/StateMachine/States/CombatState.h"
#include "Unit/UnitAI/StateMachine/States/MiningState.h"

State *IdleState::RunCurrentState() {

    //from Idle to Movement
    if(unit->hasMovementTarget){
        return MoveState;
    }
    //from Idle to Combat
    if(!unit->hasMovementTarget && unit->hasCombatTarget && unit->isTargetInRange){
        return CombatState;
    }

    //from Idle to Mining
    if(!unit->hasMovementTarget && !unit->hasCombatTarget && unit->hasMiningTarget && unit->isTargetInRange){
        return MiningState;
    }

    return this;

}