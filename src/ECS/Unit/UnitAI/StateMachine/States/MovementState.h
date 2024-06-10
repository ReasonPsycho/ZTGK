//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_MOVEMENTSTATE_H
#define ZTGK_MOVEMENTSTATE_H
#include "ECS/Unit/UnitAI/StateMachine/State.h"
class CombatState;
class MiningState;
class IdleState;

class MovementState : public State{

public:
    MovementState(Grid* grid);

    State* RunCurrentState() override;

    CombatState* combatState;
    MiningState* miningState;
    IdleState* idleState;

    bool isTargetInRange() override;
    bool hasCombatTarget{};
    bool isAttackTargetInRange{};
    bool canPathToAttackTarget();
    bool canPathToMiningTarget();

private:
    void MoveOnPath();
};


#endif //ZTGK_MOVEMENTSTATE_H
