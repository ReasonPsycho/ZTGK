//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_MININGSTATE_H
#define ZTGK_MININGSTATE_H
#include "ECS/Unit/UnitAI/StateMachine/State.h"
#include "ECS/Grid/Grid.h"

class MovementState;
class CombatState;
class IdleState;
class MiningState : public State{
public:
    MiningState(Grid* grid);
    State* RunCurrentState() override;
    bool isTargetInRange() override;
    MovementState* moveState;
    CombatState* combatState;
    IdleState* idleState;

private:
    void Mine();
};


#endif //ZTGK_MININGSTATE_H
