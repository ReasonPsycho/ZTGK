#include "MovementState.h"
#include "ECS/Unit/Unit.h"
#include "CombatState.h"
#include "IdleState.h"
#include "MiningState.h"
#include "ECS/Utils/Time.h"
#include "ECS/Unit/Equipment/InventoryManager.h"

// Static member initialization
std::unique_ptr<MovementState> MovementState::instance = nullptr;

// Constructor
MovementState::MovementState(Grid* grid, Unit* unit){
    this->name = "Movement";
    this->grid = grid;
    this->unit = unit;
}

// Static method to get the instance of MovementState
std::unique_ptr<MovementState> MovementState::getInstance(Grid* grid, Unit* unit) {
    if (!instance) {
        instance = std::unique_ptr<MovementState>(new MovementState(grid, unit));
    }
    return std::unique_ptr<MovementState>(instance.get());
}

// Method to run the current state
std::unique_ptr<State> MovementState::RunCurrentState() {

    MoveOnPath();

    if (unit->hasPickupTarget && glm::distance(unit->worldPosition, unit->pickupTarget->getEntity()->transform.getGlobalPosition()) <= 1.5) {
        std::pair<Item *, Item *> drop = {unit->equipment[1], unit->equipment[2]};
        InventoryManager::instance->assign_item(unit->pickupTarget->item, unit, -1);
        if (drop.first)
            InventoryManager::instance->spawn_item_on_map(drop.first, {unit->worldPosition.x, unit->worldPosition.z});
        if (drop.second)
            InventoryManager::instance->spawn_item_on_map(drop.second,
                                                          {unit->worldPosition.x + 0.2, unit->worldPosition.z + 0.2});

        unit->pickupTarget->getEntity()->Destroy();
        unit->pickupTarget = nullptr;
        unit->hasPickupTarget = false;
    }

    if(unit->hasMovementTarget){
        return getInstance(grid, unit);
    }

    //from Movement to Idle
    if (!unit->hasMovementTarget && !unit->hasCombatTarget && !unit->hasMiningTarget) {
        auto idleState = IdleState::getInstance(grid, unit);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(1.5, 5.0);
        double random_number = dis(gen);

        idleState->randomTime = random_number;

        return std::move(idleState);
    }

    //from Movement to Combat
    if (unit->hasCombatTarget) {
        auto combatState = CombatState::getInstance(grid, unit);

        if(combatState->isTargetInRange())
            return std::move(combatState);
        else
        {
            unit->hasMovementTarget = true;
            unit->movementTarget = unit->combatTarget->gridPosition;
            return std::make_unique<MovementState>(grid, unit);
        }
    }

    //from Movement to Mining
    if (unit->hasMiningTarget) {
        auto miningState = MiningState::getInstance(grid, unit);

        if(miningState->isTargetInRange())
            return std::move(miningState);
        else
        {
            auto closestMineable = unit->findClosestMineable();
            if(closestMineable != nullptr) {
                unit->hasMovementTarget = true;
                unit->movementTarget = unit->findClosestMineable()->gridPosition;
                unit->currentMiningTarget = nullptr;
                unit->hasMiningTarget = false;
            }
            else{
                unit->hasMiningTarget = false;
                auto idleState = IdleState::getInstance(grid, unit);
                return std::move(idleState);
            }
            return getInstance(grid, unit);
        }
    }

    return getInstance(grid, unit);
}

void MovementState::MoveOnPath() {
    if (unit->pathfinding.path.size() == 0 && !unit->hasMovementTarget) {
        return;
    }

    if(unit->pathfinding.path.size() == 0 && unit->hasMovementTarget){
        unit->pathfinding.FindPath(unit->gridPosition, unit->movementTarget);
    }
    if (unit->pathfinding.path.size() > 0) {
        Vector2Int nextTile = unit->pathfinding.path[0];
        glm::vec3 nextTileWorldPosition = unit->grid->GridToWorldPosition(nextTile);
        if(unit->worldPosition == nextTileWorldPosition){
            unit->pathfinding.path.erase(unit->pathfinding.path.begin());
            if (unit->pathfinding.path.size() == 0) {
                unit->hasMovementTarget = false;
                return;
            }
        }
        else{
            float rotationAngle = atan2(nextTileWorldPosition.x - unit->worldPosition.x, nextTileWorldPosition.z - unit->worldPosition.z);
            Vector3 worldPos = Vector3(unit->worldPosition.x, unit->worldPosition.y, unit->worldPosition.z);
            Vector3 nextWorldPos = Vector3(nextTileWorldPosition.x, nextTileWorldPosition.y, nextTileWorldPosition.z);
            Vector3 moveTowards = VectorUtils::MoveTowards(worldPos, nextWorldPos, (unit->stats.move_spd + unit->stats.added.move_speed) * Time::Instance().DeltaTime());
            unit->worldPosition = glm::vec3(moveTowards.x, moveTowards.y, moveTowards.z);
            unit->rotation = rotationAngle;
        }
    }
}

bool MovementState::isTargetInRange() {
    return false;
}
