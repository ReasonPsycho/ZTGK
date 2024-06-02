#include "MiningState.h"
#include "ECS/Unit/Unit.h"
#include "ECS/Unit/UnitAI/StateMachine/State.h"
#include "MovementState.h"
#include "CombatState.h"
#include "IdleState.h"

// Static member initialization
std::unique_ptr<MiningState> MiningState::instance = nullptr;

// Constructor
MiningState::MiningState(Grid* grid, Unit* unit){
    this->name = "Mining";
    this->grid = grid;
    this->unit = unit;
}

// Static method to get the instance of MiningState
std::unique_ptr<MiningState> MiningState::getInstance(Grid* grid, Unit* unit) {
    if (!instance) {
        instance = std::unique_ptr<MiningState>(new MiningState(grid, unit));
    }
    return std::unique_ptr<MiningState>(instance.get());
}

// Method to run the current state
std::unique_ptr<State> MiningState::RunCurrentState() {
    isTargetInRange();

    //from Mining to Idle
    if(!unit->hasMovementTarget && !unit->hasCombatTarget && !unit->hasMiningTarget){
        auto idleState = IdleState::getInstance(grid, unit);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(1.5, 5.0);
        double random_number = dis(gen);

        idleState->randomTime = random_number;

        return std::move(idleState);
    }

    //from Mining to Movement
    if(unit->hasMovementTarget){
        auto moveState = MovementState::getInstance(grid, unit);

        return std::move(moveState);
    }

    //from Mining to Combat
    if(isTargetInRange()) {
        Mine();
        return getInstance(grid, unit);
    }
    else if (unit->hasMiningTarget && !isTargetInRange()) {
        auto moveState = MovementState::getInstance(grid, unit);
        unit->hasMovementTarget = true;
        unit->movementTarget = unit->pathfinding.GetNearestVacantTile(unit->currentMiningTarget->gridPosition, unit->gridPosition);
        return std::move(moveState);
    }
    if(unit->hasCombatTarget){
        auto combatState = CombatState::getInstance(grid, unit);

        if(combatState->isTargetInRange())
            return std::move(combatState);
        else
        {
            unit->hasMovementTarget = true;
            unit->movementTarget = unit->combatTarget->gridPosition;
            auto moveState = MovementState::getInstance(grid, unit);
            return std::move(moveState);
        }
    }
    return nullptr;
}

bool MiningState::isTargetInRange() {
    IMineable* current = unit->currentMiningTarget;
    if(current == nullptr){
        spdlog::error("IN MiningState::isTargetInRange(): no current mining target");
        unit->hasMiningTarget = false;
        unit->isTargetInRange = false;
        return false;
    }

    if(VectorUtils::Distance(VectorUtils::GlmVec3ToVector3(unit->worldPosition), VectorUtils::GlmVec3ToVector3(grid->GridToWorldPosition(current->gridPosition))) <=/*todo this is the old range value ??*/ 3){
        unit->isTargetInRange = true;
        return true;
    }
    return false;
}

void MiningState::Mine() {
    std::vector<IMineable *> miningTargets = unit->miningTargets;

    if (miningTargets.empty()) {
        spdlog::error("In MiningState::Mine(): Mining targets are empty");
        unit->hasMiningTarget = false;
        return;
    }


    if (unit->currentMiningTarget->getTimeToMineRemaining() <= 0 && miningTargets.size() == 1) {
        unit->hasMiningTarget = false;
        miningTargets.clear();
        unit->miningTargets.clear();
        return;
    }

    if (isTargetInRange()) {
        unit->currentMiningTarget->Mine(unit);
        if (unit->currentMiningTarget->getTimeToMineRemaining() <= 0) {
            miningTargets.erase(miningTargets.begin());
            if (miningTargets.empty()) {
                unit->hasMiningTarget = false;
                unit->currentMiningTarget = nullptr;
                return;
            }
            unit->sortMiningTargetsByDistance();
            unit->currentMiningTarget = miningTargets.front();
        }
    }
}
