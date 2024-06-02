#ifndef MOVEMENTSTATE_H
#define MOVEMENTSTATE_H

#include "ECS/Unit/UnitAI/StateMachine/State.h"

class MovementState : public State {
public:
    // Constructor
    MovementState(Grid* grid, Unit* unit);

    // Static method to get the instance of MovementState
    static std::unique_ptr<MovementState> getInstance(Grid* grid, Unit* unit);

    // Methods
    std::unique_ptr<State> RunCurrentState() override;
    bool isTargetInRange() override;

private:
    void MoveOnPath();
    static std::unique_ptr<MovementState> instance;

};

#endif // MOVEMENTSTATE_H
