#include "IdleState.h"
#include "ECS/Unit/Unit.h"
#include "MovementState.h"
#include "CombatState.h"
#include "MiningState.h"
#include "ECS/Utils/Time.h"

// Static member initialization
std::unique_ptr<IdleState> IdleState::instance = nullptr;

// Constructor
IdleState::IdleState(Grid* grid, Unit* unit){
    this->name = "Idle";
    this->grid = grid;
    this->unit = unit;
}

// Static method to get the instance of IdleState
std::unique_ptr<IdleState> IdleState::getInstance(Grid* grid, Unit* unit) {
    if (!instance) {
        instance = std::unique_ptr<IdleState>(new IdleState(grid, unit));
    }
    auto ins = std::unique_ptr<IdleState>(instance.get());
    return std::unique_ptr<IdleState>(instance.get());
}

// Method to run the current state
std::unique_ptr<State> IdleState::RunCurrentState() {
    // Check for movement target
    if (unit->hasMovementTarget) {
        auto moveState = MovementState::getInstance(grid, unit);
        idleTimer = 0;
        return std::move(moveState);
    }

    // Check for combat target
    if (unit->hasCombatTarget) {
        auto combatState = CombatState::getInstance(grid, unit);

        if (combatState->isTargetInRange()) {
            idleTimer = 0;
            return std::move(combatState);
        } else {
            unit->hasMovementTarget = true;
            unit->movementTarget = unit->combatTarget->gridPosition;
            auto moveState = MovementState::getInstance(grid, unit);

            idleTimer = 0;
            return std::move(moveState);
        }
    }

    // Check for mining target
    if (unit->hasMiningTarget) {
        auto miningState = MiningState::getInstance(grid, unit);

        if (miningState->isTargetInRange()) {
            idleTimer = 0;
            return std::move(miningState);
        } else {
            unit->hasMovementTarget = true;
            IMineable* mineable = unit->findClosestMineable();
            if (mineable != nullptr) {
                unit->movementTarget = mineable->gridPosition;
                auto moveState = MovementState::getInstance(grid, unit);
                idleTimer = 0;
                return std::move(moveState);
            } else {
                idleTimer += Time::Instance().DeltaTime();
                return getInstance(grid, unit);
            }
        }
    }

    // Increment idle timer
    idleTimer += Time::Instance().DeltaTime();

    // Check if it's time to perform a random movement
    if (idleTimer > randomTime && unit->isAlly) {
        unit->hasMovementTarget = true;
        unit->movementTarget = unit->GetDirtiestTileAround();
        auto moveState = MovementState::getInstance(grid, unit);
        idleTimer = 0;
        return std::move(moveState);
    }

    // Stay in idle state
    return getInstance(grid, unit);
}

// Method to check if the target is in range
bool IdleState::isTargetInRange() {
    return false;
}
