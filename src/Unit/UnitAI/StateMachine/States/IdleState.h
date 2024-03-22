//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_IDLESTATE_H
#define ZTGK_IDLESTATE_H
#include "../State.h"
#include "MovementState.h"
#include "CombatState.h"

class IdleState : public State{
public:
    State* RunCurrentState() override;

    MovementState* MoveState;
    CombatState* CombatState;
    bool canSeeUnitTarget;
};


#endif //ZTGK_IDLESTATE_H
