#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "ECS/Unit/UnitAI/StateMachine/State.h"
#include <memory>

class IdleState : public State {
public:
    // Constructor
    IdleState(Grid* grid, Unit* unit);

    // Static method to get the instance of IdleState
    static std::unique_ptr<IdleState> getInstance(Grid* grid, Unit* unit);

    // Methods
    std::unique_ptr<State> RunCurrentState() override;
    bool isTargetInRange() override;

    double randomTime = 3;
    double idleTimer = 0;

private:
    // Static member to hold the singleton instance
    static std::unique_ptr<IdleState> instance;
};

#endif // IDLESTATE_H
