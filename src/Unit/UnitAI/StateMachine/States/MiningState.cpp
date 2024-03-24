//
// Created by igork on 22.03.2024.
//

#include "MiningState.h"

#include "Unit/Unit.h"
#include "Unit/UnitAI/StateMachine/State.h"
#include "Unit/UnitAI/StateMachine/States/MovementState.h"
#include "Unit/UnitAI/StateMachine/States/CombatState.h"
#include "Unit/UnitAI/StateMachine/States/IdleState.h"


State *MiningState::RunCurrentState() {

    //from Mining to Idle
    if(!unit->hasMovementTarget && !unit->hasCombatTarget && !unit->hasMiningTarget){
        return IdleState;
    }

    //from Mining to Movement
    if(unit->hasMovementTarget){
        return MoveState;
    }

    //from Mining to Combat
    if(!unit->hasMovementTarget && unit->hasCombatTarget && unit->isTargetInRange){
        return CombatState;
    }

    return this;
}