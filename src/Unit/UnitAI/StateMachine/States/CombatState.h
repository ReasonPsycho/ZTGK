//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_COMBATSTATE_H
#define ZTGK_COMBATSTATE_H


#include "../State.h"

class CombatState : public State{
public:
    State* RunCurrentState() override;

    MovementState *MoveState;
    MiningState* MiningState;
    IdleState* IdleState;
};


#endif //ZTGK_COMBATSTATE_H
