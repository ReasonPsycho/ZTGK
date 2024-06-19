//
// Created by igork on 22.03.2024.
//

#include "IdleState.h"
#include "ECS/Unit/Unit.h"
#include "MovementState.h"
#include "CombatState.h"
#include "MiningState.h"
#include "ECS/Utils/Time.h"
#include "HealingState.h"
#include <random>
#include "ECS/Gameplay/WashingMachineTile.h"
#include "ECS/Render/Components/AnimationPlayer.h"

State *IdleState::RunCurrentState() {

    if(!unit->isAlive && unit->isAlly){
        auto neighs = grid->GetNeighbours(unit->gridPosition);
        for(auto n : neighs){
            if(n->getEntity()->getComponent<WashingMachineTile>() != nullptr){
                auto healingState = new HealingState(grid, unit);
                return healingState;
            }
        }
        auto moveState = new MovementState(grid);
        moveState->unit = unit;
        moveState->unit->movementTarget = unit->pathfinding.GetNearestVacantTile(unit->getClosestWashingMachineTile(), unit->gridPosition);
        return moveState;
    }

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

    auto currentTile = grid->getTileAt(unit->gridPosition);

    if (unit->isAlly && currentTile->dirtinessLevel > 0) {
        auto anim = unit->getEntity()->getComponent<AnimationPlayer>();
        if (anim == nullptr) {
        } else if(!unit->playinIdleAnimation) {
            string modelPathGabkaIdle = "res/models/gabka/pan_gabka_idle.fbx";
            anim->PlayAnimation(modelPathGabkaIdle, true, 2.0f);
            if(!unit->playinIdleAnimation)
                ztgk::game::audioManager->playRandomSoundFromGroup("idle");
            unit->playinIdleAnimation = true;

        }
        auto newDirtLvl = currentTile->dirtinessLevel - 30 * Time::Instance().DeltaTime();
        if (newDirtLvl < 0) {
            newDirtLvl = 0;
        }
        currentTile->changeDirtinessLevel(newDirtLvl);
        if (newDirtLvl == 0) {

        }
    }

    else if (!unit->isAlly && currentTile->dirtinessLevel < 100) {
        auto newDirtLvl = currentTile->dirtinessLevel + 10 * Time::Instance().DeltaTime();
        if (newDirtLvl > 100) {
            newDirtLvl = 100;
        }
        currentTile->changeDirtinessLevel(newDirtLvl);
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
