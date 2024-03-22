//
// Created by igork on 22.03.2024.
//

#include "CombatState.h"

State *CombatState::RunCurrentState() {
    if(isAttackTargetInRange){
        return this;
    } else {
        return MoveState;
    }
}