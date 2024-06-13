//
// Created by igork on 22.03.2024.
//

#include "IdleState.h"
#include "ECS/Unit/Unit.h"
#include "MovementState.h"
#include "CombatState.h"
#include "MiningState.h"
#include "ECS/Utils/Time.h"
#include <random>

State *IdleState::RunCurrentState() {

    //from Idle to Movement
    if(unit->hasMovementTarget){
        moveState = new MovementState(grid);
        moveState->unit = unit;
        idleTimer = 0;
        return moveState;
    }
    //from Idle to Combat

    if(unit->hasCombatTarget && unit->combatTarget != nullptr){

        combatState = new CombatState(grid);
        combatState->unit = unit;

        if(combatState->isTargetInRange() && unit->canPathToAttackTarget()) {
            idleTimer = 0;
            return combatState;
        }
        else if(unit->canPathToAttackTarget())
        {
            unit->hasMovementTarget = true;
            unit->movementTarget = unit->combatTarget->gridPosition;
            moveState = new MovementState(grid);
            moveState->unit = unit;
            idleTimer = 0;
            return moveState;
        }
    }

    //from Idle to Mining
    if(unit->hasMiningTarget){
        miningState = new MiningState(grid);
        miningState->unit = unit;

        if(miningState->isTargetInRange()) {
            idleTimer = 0;
            return miningState;
        }
        else
        {
            unit->hasMovementTarget = true;
            IMineable* mineable = unit->findClosestMineable();
            if(mineable != nullptr) {
                unit->movementTarget = unit->findClosestMineable()->gridPosition;
                moveState = new MovementState(grid);
                moveState->unit = unit;
                idleTimer = 0;
                return moveState;
            }
            else
                idleTimer += Time::Instance().DeltaTime();
                return this;

        }
    }

    idleTimer += Time::Instance().DeltaTime();

    if(idleTimer > randomTime && unit->isAlly){
        unit->hasMovementTarget = true;
        unit->movementTarget = unit->GetDirtiestTileAround();
        moveState = new MovementState(grid);
        moveState->unit = unit;
        idleTimer = 0;
        return moveState;
    }
    return this;

}

bool IdleState::isTargetInRange() {
    return false;
}

IdleState::IdleState(Grid *grid) {
    this->grid = grid;
    this->name = "Idle";

}
