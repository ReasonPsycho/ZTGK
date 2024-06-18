//
// Created by igork on 22.03.2024.
//

#include "MovementState.h"
#include "ECS/Unit/Unit.h"
#include "CombatState.h"
#include "IdleState.h"
#include "MiningState.h"
#include "ECS/Utils/Time.h"
#include "ECS/Unit/Equipment/InventoryManager.h"
#include "ECS/Unit/UnitSystem.h"
#include "HealingState.h"
#include "ECS/Gameplay/WashingMachineTile.h"
#include "ECS/Render/Components/AnimationPlayer.h"

State *MovementState::RunCurrentState() {

    if(!unit->isAlive && unit->isAlly){
        auto neighs = grid->GetNeighbours(unit->gridPosition);
        for(auto n : neighs){
            if(n->getEntity()->getComponent<WashingMachineTile>() != nullptr){
                auto healingState = new HealingState(grid, unit);
                return healingState;
            }
        }
        unit->movementTarget = unit->pathfinding.GetNearestVacantTile(unit->getClosestWashingMachineTile(), unit->gridPosition);
        MoveOnPath();
        return this;
    }

    MoveOnPath();

    // todo calculate from centers
    if (unit->hasPickupTarget && unit->pickupTarget != nullptr && glm::distance(unit->worldPosition, unit->pickupTarget->getEntity()->transform.getGlobalPosition()) <= 1.5) {
        unit->Pickup(unit->pickupTarget);
    }
    // todo idk if this is necessary
    if(unit->hasPickupTarget && unit->pickupTarget == nullptr){
        unit->hasPickupTarget = false;
    }

    if(unit-> hasCombatTarget && unit->combatTarget != nullptr){
        auto combat = new CombatState(grid);
        combat->unit = unit;
        if(combat->isTargetInRange()){
            unit->hasMovementTarget = false;
            return combat;
        }
        else {
            unit->hasMovementTarget = true;
            unit->movementTarget = unit->pathfinding.GetNearestVacantTileInRange(unit->gridPosition,
                                                                                 unit->combatTarget->gridPosition,
                                                                                 unit->stats.added.rng_add +
                                                                                 unit->stats.added.rng_rem);
            return  this;
        }

    }

    if(unit->hasMovementTarget && (unit->hasMiningTarget && unit->currentMiningTarget != nullptr)){
        return this;
    }


    //from Movement to Idle
    if (!unit->hasMovementTarget && !unit->hasCombatTarget && !unit->hasMiningTarget) {
        idleState = new IdleState(grid);
        idleState->unit = unit;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(1.5, 5.0);
        double random_number = dis(gen);

        idleState->randomTime = random_number;

        return idleState;
    }


    //from Movement to Mining
    if (unit->hasMiningTarget) {
        miningState = new MiningState(grid);
        miningState->unit = unit;

        if (miningState->isTargetInRange() && unit->canPathToMiningTarget())
            return miningState;
        else if (unit->canPathToMiningTarget()) {
            auto closestMineable = unit->findClosestMineable();
            if (closestMineable != nullptr) {
                unit->hasMovementTarget = true;
                unit->movementTarget = closestMineable->gridPosition;
                unit->currentMiningTarget = closestMineable;
                unit->hasMiningTarget = true;
                return this;
                //spdlog::info("Target not in range, moving to mining target");
            } else {
                unit->hasMiningTarget = false;
                idleState = new IdleState(grid);
                idleState->unit = unit;
                //spdlog::info("No mineable targets found, returning to idle state");
                return idleState;
            }
        }
    }

    //from Movement to Combat
    if (unit->hasCombatTarget) {
        combatState = new CombatState(grid);
        combatState->unit = unit;

        if(combatState->isTargetInRange() && unit->canPathToAttackTarget())
            return combatState;
        else if(unit->canPathToAttackTarget())
        {
            delete combatState;
            unit->hasMovementTarget = true;
            unit->movementTarget = unit->combatTarget->gridPosition;
            return this;
        }
        else{
            delete combatState;
            unit->hasCombatTarget = false;
            unit->combatTarget = nullptr;
        }
    }


    return this;
}

void MovementState::MoveOnPath() {
    //if any tile in path is not vacant, recalculate path
//    for (auto tile : unit->pathfinding.path) {
//        if (!unit->grid->getTileAt(tile.x, tile.z)->vacant()) {
//            spdlog::error("Non vacant tile in path, recalculating path");
//            unit->pathfinding.FindPath(unit->gridPosition, unit->movementTarget, ztgk::game::scene->systemManager.getSystem<UnitSystem>()->getAllUnitsPositionsExceptMe(unit));
//            break;
//        }
//    }

    //if path is not empty and next tile is not vacant, recalculate path
    if (unit->pathfinding.path.size() > 0 && (!unit->grid->getTileAt(unit->pathfinding.path[0].x, unit->pathfinding.path[0].z)->vacant() && unit->pathfinding.path[0] != unit->gridPosition)) {
        spdlog::error("Non vacant tile in path, recalculating path");
        unit->pathfinding.FindPath(unit->gridPosition, unit->movementTarget, ztgk::game::scene->systemManager.getSystem<UnitSystem>()->getAllUnitsPositionsExceptMe(unit));
    }


    if (unit->pathfinding.path.size() == 0 && !unit->hasMovementTarget) {
        return;
    }
    if(unit->pathfinding.path.size() == 0 && unit->hasMovementTarget){
        unit->pathfinding.FindPath(unit->gridPosition, unit->movementTarget, ztgk::game::scene->systemManager.getSystem<UnitSystem>()->getAllUnitsPositionsExceptMe(unit));
    }
    if(unit->pathfinding.path.size() > 1 &&  unit->pathfinding.path[0] == unit->gridPosition){
        unit->pathfinding.path.erase(unit->pathfinding.path.begin());
    }
    if (!unit->pathfinding.path.empty()) {



        Vector2Int nextTile = unit->pathfinding.path[0];

        glm::vec3 nextTileWorldPosition = unit->grid->GridToWorldPosition(nextTile);
        if(unit->worldPosition == nextTileWorldPosition){
            unit->pathfinding.path.erase(unit->pathfinding.path.begin());
            if (unit->pathfinding.path.size() == 0) {
                unit->hasMovementTarget = false;
                return;
            }
        }
        else{
            float rotationAngle = atan2(nextTileWorldPosition.x - unit->worldPosition.x, nextTileWorldPosition.z - unit->worldPosition.z);


            Vector3 worldPos = Vector3(unit->worldPosition.x, unit->worldPosition.y, unit->worldPosition.z);
            Vector3 nextWorldPos = Vector3(nextTileWorldPosition.x, nextTileWorldPosition.y, nextTileWorldPosition.z);
            Vector3 moveTowards = VectorUtils::MoveTowards(worldPos, nextWorldPos, (unit->isAlive ? unit->stats.move_spd + unit->stats.added.move_speed : unit->stats.move_spd_when_beaten + unit->stats.added.move_speed/2.0f) * Time::Instance().DeltaTime());
            unit->worldPosition = glm::vec3(moveTowards.x, moveTowards.y, moveTowards.z);
            unit->rotation = rotationAngle;

        }
    }
}

bool MovementState::isTargetInRange() {
    return false;
}

MovementState::MovementState(Grid *grid) {
    this->grid = grid;
    this->name = "Movement";

}


