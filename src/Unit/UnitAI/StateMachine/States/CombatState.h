//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_COMBATSTATE_H
#define ZTGK_COMBATSTATE_H

#include "Unit/UnitAI/StateMachine/State.h"
class MovementState;
class MiningState;
class IdleState;

class CombatState : public State{
public:
    State* RunCurrentState() override;
    bool isTargetInRange() override;

    MovementState *MoveState;
    MiningState* MiningState;
    IdleState* IdleState;

private:
    void AttackTarget();
};


#endif //ZTGK_COMBATSTATE_H
