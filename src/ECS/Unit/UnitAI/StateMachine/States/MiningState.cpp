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


    //from Mining to Idle
    if(!unit->hasMovementTarget && !unit->hasCombatTarget && !unit->hasMiningTarget){
        idleState = new IdleState(grid);
        idleState->unit = unit;

        return idleState;
    }

    //from Mining to Movement
    if(unit->hasMovementTarget){
        moveState = new MovementState(grid);
        moveState->unit = unit;

        return moveState;
    }

    //from Mining to Combat
    if(unit->hasCombatTarget){
        combatState = new CombatState(grid);
        combatState->unit = unit;

        if(combatState->isTargetInRange())
            return combatState;
        else
        {
            unit->hasMovementTarget = true;
            unit->movementTarget = unit->combatTarget->gridPosition;
            return this;
        }
    }

    Mine();
    return this;
}

bool MiningState::isTargetInRange() {
    if(unit->miningTarget == nullptr){
        unit->hasMiningTarget = false;
        unit->isTargetInRange = false;
        return false;
    }
     if(VectorUtils::Distance(VectorUtils::GlmVec3ToVector3(unit->worldPosition), VectorUtils::GlmVec3ToVector3(grid->GridToWorldPosition(unit->miningTarget->gridPosition))) <= unit->stats.range){
         unit->isTargetInRange = true;
         return true;
     }
     return false;
}

void MiningState::Mine() {
    if(unit->miningTarget->getTimeToMineRemaining() <= 0){
        unit->hasMiningTarget = false;
        return;
    }
    if(!unit->isTargetInRange){
        unit->hasMovementTarget = true;
        unit -> movementTarget = unit->miningTarget->gridPosition;
        return;
    }
        unit->miningTarget->Mine();
}

MiningState::MiningState(Grid *grid) {
    this->grid = grid;
    this->name = "Mining";
}

