//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_COMBATSTATE_H
#define ZTGK_COMBATSTATE_H
#include "../State.h"
#include "MovementState.h"


class CombatState : public State{
public:
    State* RunCurrentState() override;
    MovementState* MoveState;

    bool isAttackTargetInRange;
};


#endif //ZTGK_COMBATSTATE_H
