#ifndef MININGSTATE_H
#define MININGSTATE_H

#include "ECS/Unit/UnitAI/StateMachine/State.h"
#include "ECS/Grid/Grid.h"
#include "ECS/Unit/Mining/IMineable.h"
#include <unordered_set>
#include <memory>

class MiningState : public State {
public:
    // Constructor
    MiningState(Grid* grid, Unit* unit);

    // Static method to get the instance of MiningState
    static std::unique_ptr<MiningState> getInstance(Grid* grid, Unit* unit);

    // Methods
    std::unique_ptr<State> RunCurrentState() override;
    bool isTargetInRange() override;

private:
    void Mine();
    // Static member to hold the singleton instance
    static std::unique_ptr<MiningState> instance;
};

#endif // MININGSTATE_H
