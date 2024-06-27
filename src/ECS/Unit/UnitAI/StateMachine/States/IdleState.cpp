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
#include "ECS/Render/Components/BetterSpriteRender.h"

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
                unit->movementTarget = unit->pathfinding.GetNearestVacantTile(mineable->gridPosition, unit->gridPosition);
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
        } else if(unit->unitType == UnitType::UNIT_SPONGE && !unit->playinIdleAnimation) {
            string modelPathGabkaIdle = "res/models/gabka/pan_gabka_idle.fbx";
            anim->PlayAnimation(modelPathGabkaIdle, true, 2.0f);
            if(!unit->playinIdleAnimation)
                unit->speaker->PlayRandomSoundFromGroup("idle");
            unit->playinIdleAnimation = true;

            auto emote =ztgk::game::EMOTES::BUBBLE_TONGUE;
            auto randInt = RNG::RandomInt(0, 2);
            switch (randInt) {
                case 0:
                    emote = ztgk::game::EMOTES::BUBBLE_TONGUE;
                    break;
                case 1:
                    emote = ztgk::game::EMOTES::BUBBLE_HAPPY;
                    break;
                case 2:
                    emote = ztgk::game::EMOTES::BUBBLE_CUTE;
                    break;
            }
            unit->tryToSendEmote(emote);
        }

    }

    else if (!unit->isAlly && currentTile->dirtinessLevel < 100) {
        auto newDirtLvl = currentTile->dirtinessLevel + 10 * Time::Instance().DeltaTime();
        if (newDirtLvl > 100) {
            newDirtLvl = 100;
        }
        currentTile->changeDirtinessLevel(newDirtLvl);
    }

    if(!unit->isAlly){
        if(!currentTile->isInFogOfWar){
            auto emote =ztgk::game::EMOTES::P_BUBBLE_TONGUE;
            auto randInt = RNG::RandomInt(0, 2);
            switch (randInt) {
                case 0:
                    emote = ztgk::game::EMOTES::P_BUBBLE_TONGUE;
                    break;
                case 1:
                    emote = ztgk::game::EMOTES::P_BUBBLE_CUTE;
                    break;
                case 2:
                    emote = ztgk::game::EMOTES::P_BUBBLE_EEPY;
                    break;
            }
            unit->tryToSendEmote(emote);
        }

        if (unit->unitType == UNIT_BUG && !grid->getTileAt(unit->gridPosition)->isInFogOfWar) {
            auto anim = unit->getEntity()->getComponent<AnimationPlayer>();
            if(anim!= nullptr){
                string modelPathBugMove = "res/models/zuczek/Zuczek_attack - copia.fbx";
                if (unit->animationcooldown > anim->animationMap[modelPathBugMove].GetDuration() /
                                              (anim->animationMap[modelPathBugMove].GetTicksPerSecond() * 2.0f)) {
                    anim->PlayAnimation(modelPathBugMove, false, 2.0f);
                    unit->animationcooldown = 0;
                }
            }

        }
        if(unit->unitType == UNIT_SHROOM && !grid->getTileAt(unit->gridPosition)->isInFogOfWar){
            auto anim = unit->getEntity()->getComponent<AnimationPlayer>();
            if(anim!= nullptr){
                string modelPathShroomMove = "res/models/Mushroom/shroom_idle.fbx";
                if (unit->animationcooldown > anim->animationMap[modelPathShroomMove].GetDuration() /
                                              (anim->animationMap[modelPathShroomMove].GetTicksPerSecond() * 2.0f)) {
                    anim->PlayAnimation(modelPathShroomMove, false, 2.0f);
                    unit->animationcooldown = 0;
                }
            }
        }
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
