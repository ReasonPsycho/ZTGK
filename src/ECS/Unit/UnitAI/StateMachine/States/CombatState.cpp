//
// Created by igork on 22.03.2024.
//


#include "CombatState.h"
#include "ECS/Unit/Unit.h"
#include "ECS/Unit/UnitAI/StateMachine/State.h"
#include "MovementState.h"
#include "MiningState.h"
#include "IdleState.h"

State *CombatState::RunCurrentState() {

    isTargetInRange();
    AttackTarget();

    //from Combat to Idle
    if (!unit->hasMovementTarget && !unit->hasCombatTarget && !unit->hasMiningTarget) {
        return IdleState;
    }

    //from Combat to Movement
    if (unit->hasMovementTarget) {
        return MoveState;
    }

    //from Combat to Mining
    if (!unit->hasMovementTarget && !unit->hasCombatTarget && unit->hasMiningTarget && unit->isTargetInRange) {
        return MiningState;
    }

    return this;
}

bool CombatState::isTargetInRange() {
    if(unit->combatTarget == nullptr){
        unit->hasCombatTarget = false;
        return false;
    }
    Vector3 worldPosition = Vector3(unit->gridPosition.x, 0, unit->gridPosition.z);
    Vector3 combatTargetWorldPosition = Vector3(unit->combatTarget->gridPosition.x, 0, unit->combatTarget->gridPosition.z);
    if(VectorUtils::Distance(worldPosition, combatTargetWorldPosition) <= unit->stats.range){
        unit->isTargetInRange = true;
        return true;
    }
    return false;
}

void CombatState::AttackTarget() {
    if (unit-> combatTarget == nullptr) {
        unit->hasCombatTarget = false;
        return;
    }
    if(!unit->isTargetInRange){
        unit->hasMovementTarget = true;
        unit->movementTarget = unit->combatTarget->gridPosition;
        return;
    }
    //TODO: attack target
    return;
}
