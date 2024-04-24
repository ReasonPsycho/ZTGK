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
        moveState = new MovementState(grid);
        moveState->unit = unit;
        return moveState;
    }
    //from Idle to Combat
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

    //from Idle to Mining
    if(unit->hasMiningTarget){
        miningState = new MiningState(grid);
        miningState->unit = unit;

        if(miningState->isTargetInRange())
            return miningState;
        else
        {
            unit->hasMovementTarget = true;
            unit->movementTarget = unit->miningTarget->gridPosition;
            return this;
        }
    }

    return this;

}

bool IdleState::isTargetInRange() {
    return false;
}

IdleState::IdleState(Grid *grid) {
    this->grid = grid;

}
