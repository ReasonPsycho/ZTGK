//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_IDLESTATE_H
#define ZTGK_IDLESTATE_H


#include "../State.h"


class IdleState : public State{
public:
    State* RunCurrentState() override;

    MovementState* MoveState;
    CombatState* CombatState;
    MiningState* MiningState;
};


#endif //ZTGK_IDLESTATE_H
