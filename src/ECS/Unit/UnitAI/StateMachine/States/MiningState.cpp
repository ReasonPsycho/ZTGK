//
// Created by igork on 22.03.2024.
//

#include "MiningState.h"

#include "ECS/Unit/Unit.h"
#include "ECS/Unit/UnitAI/StateMachine/State.h"
#include "MovementState.h"
#include "CombatState.h"
#include "IdleState.h"


State *MiningState::RunCurrentState() {
    isTargetInRange();
    Mine();

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

bool MiningState::isTargetInRange() {
    if(unit->miningTarget == nullptr){
        unit->hasMiningTarget = false;
        unit->isTargetInRange = false;
        return false;
    }
    // if(unit->miningTarget != nullptr && VectorUtils::Distance(unit->worldPosition, unit->miningTarget->worldPosition) <= unit->stats.range){
    //     unit->isTargetInRange = true;
    //     return true;
    // }
}

void MiningState::Mine() {
    if(unit->miningTarget == nullptr){
        unit->hasMiningTarget = false;
        return;
    }
    if(!unit->isTargetInRange){
        unit->hasMovementTarget = true;
        //TODO: unit->movementTarget = unit->miningTarget->gridPosition;
        return;
    }

    unit->miningTarget->Mine();
}

