//
// Created by igork on 22.03.2024.
//

#include "IdleState.h"

State *IdleState::RunCurrentState() {
    if(canSeeUnitTarget){
        return MoveState;
    } else {
        return this;
    }
}