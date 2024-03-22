//
// Created by igork on 22.03.2024.
//

#include "MovementState.h"

State *MovementState::RunCurrentState() {
    if(isAttackTargetInRange){
        return CombatState;
    } else {
        return this;
    }
}