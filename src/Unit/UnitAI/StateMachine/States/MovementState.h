//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_MOVEMENTSTATE_H
#define ZTGK_MOVEMENTSTATE_H
#include "Unit/UnitAI/StateMachine/State.h"
class CombatState;
class MiningState;
class IdleState;

class MovementState : public State{

public:
    State* RunCurrentState() override;

    CombatState* CombatState;
    MiningState* MiningState;
    IdleState* IdleState;

    bool hasCombatTarget{};
    bool isAttackTargetInRange{};

private:
    void MoveOnPath();
};


#endif //ZTGK_MOVEMENTSTATE_H
