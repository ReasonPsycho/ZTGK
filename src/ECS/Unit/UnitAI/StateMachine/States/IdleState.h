#ifndef ZTGK_IDLESTATE_H
#define ZTGK_IDLESTATE_H

#include "ECS/Unit/UnitAI/StateMachine/State.h"

class MovementState;
class CombatState;
class MiningState;


class IdleState : public State {
public:
    State* RunCurrentState() override;

    MovementState* MoveState;
    CombatState* CombatState;
    MiningState* MiningState;
};

#endif //ZTGK_IDLESTATE_H
