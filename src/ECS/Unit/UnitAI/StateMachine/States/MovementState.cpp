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

    if(unit->hasMovementTarget){
        return this;
    }

    //from Movement to Idle
    if (!unit->hasMovementTarget && !unit->hasCombatTarget && !unit->hasMiningTarget) {
        idleState = new IdleState(grid);
        idleState->unit = unit;

        return idleState;
    }

    //from Movement to Combat
    if (unit->hasCombatTarget) {
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

    //from Movement to Mining
    if (unit->hasMiningTarget) {
        miningState = new MiningState(grid);
        miningState->unit = unit;

        if(miningState->isTargetInRange())
            return miningState;
        else
        {
            unit->hasMovementTarget = true;
            unit->movementTarget = unit->findClosestMineable()->gridPosition;
            return this;
        }
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
            Vector3 moveTowards = VectorUtils::MoveTowards(worldPos, nextWorldPos, unit->stats.movementSpeed * Time::Instance().DeltaTime());
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
