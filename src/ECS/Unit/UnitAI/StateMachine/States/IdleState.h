#ifndef ZTGK_IDLESTATE_H
#define ZTGK_IDLESTATE_H

#include "ECS/Unit/UnitAI/StateMachine/State.h"

class MovementState;
class CombatState;
class MiningState;


class IdleState : public State {
public:
    IdleState(Grid* grid);

    State* RunCurrentState() override;

    MovementState* moveState;
    CombatState* combatState;
    MiningState* miningState;

    bool isTargetInRange() override;
};

#endif //ZTGK_IDLESTATE_H
