//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_MININGSTATE_H
#define ZTGK_MININGSTATE_H
#include "../State.h"

class MiningState : public State{
public:
    State* RunCurrentState() override;

    MovementState* MoveState;
    CombatState* CombatState;
    IdleState* IdleState;
};


#endif //ZTGK_MININGSTATE_H
