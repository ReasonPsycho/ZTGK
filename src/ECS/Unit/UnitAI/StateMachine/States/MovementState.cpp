//
// Created by igork on 22.03.2024.
//

#include "MovementState.h"
#include "ECS/Unit/Unit.h"
#include "CombatState.h"
#include "IdleState.h"
#include "MiningState.h"
#include "ECS/Utils/Time.h"


State *MovementState::RunCurrentState() {

    MoveOnPath();


    //from Movement to Idle
    if (!unit->hasMovementTarget && !unit->hasCombatTarget && !unit->hasMiningTarget) {
        return IdleState;
    }

    //from Movement to Combat
    if (!unit->hasMovementTarget && unit->hasCombatTarget && unit->isTargetInRange) {
        return CombatState;
    }

    //from Movement to Mining
    if (!unit->hasMovementTarget && !unit->hasCombatTarget && unit->hasMiningTarget && unit->isTargetInRange) {
        return MiningState;
    }

    return this;
}

void MovementState::MoveOnPath() {
    if (unit->pathfinding.path.size() == 0 && !unit->hasMovementTarget) {
        return;
    }

    if(unit->pathfinding.path.size() == 0 && unit->hasMovementTarget){
        unit->pathfinding.FindPath(unit->gridPosition, unit->movementTarget);
    }
    if (unit->pathfinding.path.size() > 0) {
        Vector2Int nextTile = unit->pathfinding.path[0];
        Vector3 nextTileWorldPosition = unit->grid->GridToWorldPosition(nextTile);
        if(unit->worldPosition == nextTileWorldPosition){
            unit->pathfinding.path.erase(unit->pathfinding.path.begin());
            if (unit->pathfinding.path.size() == 0) {
                unit->hasMovementTarget = false;
                return;
            }
        }
        else{
            unit->worldPosition = VectorUtils::MoveTowards(unit->worldPosition, nextTileWorldPosition, unit->stats.movementSpeed * Time::Instance().DeltaTime());
        }
    }
}
