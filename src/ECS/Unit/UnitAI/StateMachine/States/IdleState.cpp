//
// Created by igork on 22.03.2024.
//

#include "IdleState.h"
#include "ECS/Unit/Unit.h"
#include "MovementState.h"
#include "CombatState.h"
#include "MiningState.h"

State *IdleState::RunCurrentState() {

    //from Idle to Movement
    if(unit->hasMovementTarget){
        MoveState = new MovementState();
        MoveState->unit = unit;
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

bool IdleState::isTargetInRange() {
    return false;
}
