//
// Created by igork on 22.03.2024.
//

#include "Unit.h"

#include <utility>
#include "UnitSystem.h"
#include "ECS/Utils/Globals.h"
#include "ECS/Raycasting/CollisionSystem.h"
#include "ECS/Unit/UnitAI/UnitAI.h"
#include "ECS/Unit/UnitAI/StateMachine/States/IdleState.h"
#include "ECS/Utils/Time.h"
#include <algorithm>
#include <random>

const UnitStats Unit::ALLY_BASE = {
        .max_hp = 100,
        .hp = 100,
        .move_spd = 20,
        .mine_spd = 1,
        .added = {}
};

const UnitStats Unit::ENEMY_BASE = {
        .max_hp = 100,
        .hp = 100,
        .move_spd = 20,
        .mine_spd = 1,
        .added = {}
};

Unit::Unit(std::string name, Grid *grid, Vector2Int gridPosition, UnitStats baseStats, bool isAlly)
: equipment(this) {
    this->name = std::move(name);
    this->grid = grid;
    this->gridPosition = gridPosition;
    this->worldPosition = grid->GridToWorldPosition(gridPosition);
    this->pathfinding = AstarPathfinding(grid);
    this->stats = baseStats;
    this->isAlly = isAlly;
    this->previousGridPosition = gridPosition;
    grid->getTileAt(gridPosition)->state = UNIT;
    grid->getTileAt(gridPosition)->unit = this;
    UpdateStats();
}

Unit::~Unit() {

}

bool Unit::IsAlly() const {
    return isAlly;
}

void Unit::EquipItem(Item item, short slot) {
    // todo assigning address of copied item, take by reference or pointer instead
    equipment.equipItem(&item, slot);
    UpdateStats();
}

void Unit::UnequipItem(short slot) {
    equipment.unequipItem(slot);
    UpdateStats();
}

void Unit::UpdateStats() {
    glm::ivec2 old_range = {stats.added.rng_add, stats.added.rng_rem};

    stats.added = {};
    if(equipment.item1 != nullptr){
        stats.added += equipment.item1->stats.add_to_unit;
    }
    if(equipment.item2 != nullptr){
        stats.added += equipment.item2->stats.add_to_unit;
    }

    glm::ivec2 new_range = {stats.added.rng_add, stats.added.rng_rem};
    if (new_range != old_range) {
        equipment.rangeEff0 = equipment.item0->stats.range.merge(stats.added.rng_add, stats.added.rng_rem);
        if (equipment.item1 != nullptr)
            equipment.rangeEff1 = equipment.item1->stats.range.merge(stats.added.rng_add, stats.added.rng_rem);
        if (equipment.item2 != nullptr)
            equipment.rangeEff2 = equipment.item2->stats.range.merge(stats.added.rng_add, stats.added.rng_rem);
    }

    if (stats.hp > stats.max_hp + stats.added.max_hp) {
        stats.hp = stats.max_hp + stats.added.max_hp;
    }
}

UnitStats Unit::GetBaseStats() {
    return this->stats;
}

void Unit::showImGuiDetailsImpl(Camera *camera) {

    ImGui::Text("ID %d", uniqueID);
    ImGui::Text("Unit: %s", name.c_str());
    ImGui::Text("Grid Position: (%d, %d)", gridPosition.x, gridPosition.z);
    ImGui::Text("World Position: (%f, %f, %f)", worldPosition.x, worldPosition.y, worldPosition.z);
    ImGui::Text("Ally: %s", isAlly ? "true" : "false");
    ImGui::Text("Selected: %s", isSelected ? "true" : "false");
//    ImGui::Text("Current State: %s", currentState->name.c_str());
    ImGui::Text("HP %f / %f (%f + %f)", stats.hp, stats.max_hp + stats.added.max_hp, stats.max_hp, stats.added.max_hp);
    if (ImGui::CollapsingHeader(std::format("Added stats:##+stats_unit_{}", uniqueID).c_str())) {
        stats.added.imgui_preview();
    }
    if (ImGui::CollapsingHeader(std::format("Equipment:##eq_unit_{}", uniqueID).c_str()))
        equipment.imgui_preview();
    ImGui::Text("Has movement target? %s", hasMovementTarget ? "true" : "false");
    ImGui::Text("Movement Target: (%d, %d)", movementTarget.x, movementTarget.z);
    ImGui::Text("Has combat target? %s", hasCombatTarget ? "true" : "false");
    ImGui::Text("Combat Target: %s", combatTarget != nullptr ? combatTarget->name.c_str() : "This sponge is pacifist");
    ImGui::Text("Has mining target? %s", hasMiningTarget ? "true" : "false");
    ImGui::Text("Mining Target: %s", currentMiningTarget != nullptr ? currentMiningTarget->name.c_str() : "No mining target");


}

void Unit::UpdateImpl() {
    // Handle forced idle state
    if (forcedIdleState) {
        currentState = std::make_unique<IdleState>(grid, this);
        currentState->unit = this;
        waitTimer -= Time::Instance().DeltaTime();

        if (waitTimer <= 0) {
            forcedIdleState = false;
            waitTimer = 0;
        } else {
            return;
        }
    }

    // Update dirtiness level based on ally status
    auto currentTile = grid->getTileAt(gridPosition);
    if (isAlly && currentTile->dirtinessLevel > 0) {
        auto newDirtLvl = currentTile->dirtinessLevel - 30 * Time::Instance().DeltaTime();
        currentTile->changeDirtinessLevel(std::max(newDirtLvl, 0.0));
    } else if (!isAlly && currentTile->dirtinessLevel < 100) {
        auto newDirtLvl = currentTile->dirtinessLevel + 10 * Time::Instance().DeltaTime();
        currentTile->changeDirtinessLevel(std::min(newDirtLvl, 100.0));
    }

    // Clear mined targets and update current mining target
    if (currentMiningTarget != nullptr && currentMiningTarget->isMined) {
        currentMiningTarget = nullptr;
    }

    miningTargets.erase(
            std::remove_if(miningTargets.begin(), miningTargets.end(),
                           [](const auto& mineable) { return mineable->isMined; }),
            miningTargets.end()
    );

    if (!miningTargets.empty() && currentMiningTarget == nullptr) {
        currentMiningTarget = findClosestMineable();
        hasMiningTarget = (currentMiningTarget != nullptr);
    }

    // Handle movement target
    if (hasMovementTarget) {
        if (!grid->getTileAt(movementTarget)->vacant()) {
            movementTarget = pathfinding.GetNearestVacantTile(movementTarget, gridPosition);
            pathfinding.FindPath(gridPosition, movementTarget);
            if (!pathfinding.path.empty() && pathfinding.path.front() == gridPosition) {
                pathfinding.path.erase(pathfinding.path.begin());
            }
        }
    }

    // Update grid position
    gridPosition = grid->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(worldPosition));

    // Update combat target
    combatTarget = GetClosestEnemyInSight();
    hasCombatTarget = (combatTarget != nullptr);

    // Update grid tile states and unit positions
    if (gridPosition != previousGridPosition) {
        grid->getTileAt(previousGridPosition)->state = FLOOR;
        grid->getTileAt(gridPosition)->state = UNIT;
        grid->getTileAt(previousGridPosition)->unit = nullptr;
        grid->getTileAt(gridPosition)->unit = this;
    }

    // Update entity transform
    getEntity()->transform.setLocalPosition(worldPosition);
    if (currentRotation > rotation) {
        currentRotation -= 0.1f;
    } else if (currentRotation < rotation) {
        currentRotation += 0.1f;
    }
    if(std::abs(currentRotation - rotation) < 0.1f){
        currentRotation = rotation;
    }
    getEntity()->transform.setLocalRotation(glm::vec3(0, currentRotation, 0));

    // Update previous grid position
    previousGridPosition = gridPosition;

    // Handle equipment cooldowns
    auto updateCooldown = [](float& cooldown) {
        if (cooldown > 0) {
            cooldown -= Time::Instance().DeltaTime();
        }
    };
    updateCooldown(equipment.item0->cd_sec);
    if (equipment.item1 != nullptr) {
        updateCooldown(equipment.item1->cd_sec);
    }
    if (equipment.item2 != nullptr) {
        updateCooldown(equipment.item2->cd_sec);
    }
    updateCooldown(equipment.cd_between_sec);
}


Unit *Unit::GetClosestEnemyInWeaponRange() {
    std::vector<Unit*> enemies;

    bool mySide = isAlly;
    if (equipment.use_default()) {
        auto found = equipment.rangeEff0.find_enemies({gridPosition.x, gridPosition.z}, mySide);
        enemies.insert(enemies.end(), found.begin(), found.end());
    } else {
        if (equipment.item1 != nullptr && equipment.item1->offensive) {
            auto found = equipment.rangeEff1.find_enemies({gridPosition.x, gridPosition.z}, mySide);
            enemies.insert(enemies.end(), found.begin(), found.end());
        }
        if (equipment.item2 != nullptr && equipment.item2->offensive) {
            auto found = equipment.rangeEff2.find_enemies({gridPosition.x, gridPosition.z}, mySide);
            enemies.insert(enemies.end(), found.begin(), found.end());
        }
    }

    if (enemies.empty())
        return nullptr;

    // todo see if this kills performance
    std::sort(enemies.begin(), enemies.end(), [this](Unit * enemy, Unit * enemy1){
        return VectorUtils::Distance(this->gridPosition, enemy->gridPosition) < VectorUtils::Distance(this->gridPosition, enemy1->gridPosition);
    });
    return enemies.at(0);
//

}

bool Unit::canFindPathToTarget(Vector2Int target) {
    pathfinding.FindPath(gridPosition, target);
    return !pathfinding.path.empty();
}

void Unit::serializer_init(Grid * pGrid) {
    auto playerUnit = getEntity();
    auto stateManager = new StateManager(playerUnit->getComponent<Unit>());
    stateManager->currentState = std::make_unique<IdleState>(pGrid, this);
    stateManager->currentState->unit = playerUnit->getComponent<Unit>();
    playerUnit->addComponent(make_unique<UnitAI>(playerUnit->getComponent<Unit>(), stateManager));

    // the rest is taken care of by the serializer, all we set here are extra assignments that aren't just a param copy (except for the pGrid ptr)
    this->grid = pGrid;
    this->worldPosition = pGrid->GridToWorldPosition(gridPosition);
    this->pathfinding = AstarPathfinding(pGrid);
    this->previousGridPosition = gridPosition;
    UpdateStats();
}

Entity *Unit::serializer_newUnitEntity(Scene * scene, const std::string & name) {
    auto playerUnit = scene->addEntity(name);
    playerUnit->addComponent(make_unique<Render>(ztgk::game::cube_model));
    playerUnit->transform.setLocalScale(glm::vec3(1, 1, 1));
    playerUnit->transform.setLocalRotation(glm::vec3(0, 0, 0));
    playerUnit->updateSelfAndChild();
    playerUnit->addComponent(make_unique<BoxCollider>(playerUnit, glm::vec3(2, 2, 2)));
    playerUnit->getComponent<BoxCollider>()->setCenter(playerUnit->transform.getGlobalPosition() + glm::vec3(0, 0, 0.5));
    playerUnit->addComponent(make_unique<Unit>());
    return playerUnit;
}

IMineable *Unit::findClosestMineable(const std::vector<IMineable>& MineablesToExclude) {
    ZoneScopedN("Find closest mineable");
    if(miningTargets.empty()){
        spdlog::error("IN UNIT::findClosestMineable: No mining targets!");
        return nullptr;
    }

    IMineable* closestMineable = nullptr;

    float closestDistance = 1000000;
    for (auto tile : miningTargets) {
        for(auto &excluded : MineablesToExclude){
            if(tile->gridPosition == excluded.gridPosition){
                continue;
            }
        }
        float distance = VectorUtils::Distance(Vector2Int(gridPosition.x, gridPosition.z), Vector2Int(tile->gridPosition.x, tile->gridPosition.z));
        if(distance < closestDistance){
            if(pathfinding.FindPath(gridPosition, pathfinding.GetNearestVacantTile(tile->gridPosition, gridPosition)).empty()){
                continue;
            }

            closestDistance = distance;
            closestMineable = tile;
        }
    }
    if(closestMineable == nullptr){
        spdlog::error("IN UNIT::findClosestMineable: No reachable mining target in area!");
        Wait(2);
    }

    return closestMineable;
}

void Unit::sortMiningTargetsByDistance() {
    std::sort(miningTargets.begin(), miningTargets.end(), [this](IMineable* mineable, IMineable* mineable1){
        return VectorUtils::Distance(this->gridPosition, Vector2Int(mineable->gridPosition.x, mineable->gridPosition.z)) < VectorUtils::Distance(this->gridPosition, Vector2Int(mineable1->gridPosition.x, mineable1->gridPosition.z));
    });

}

void Unit::Wait(float seconds) {
    forcedIdleState = true;
    waitTimer = seconds;

}

std::vector<Unit *> Unit::GetEnemiesInSight() {
    std::vector<Unit*> enemies;
    int sightRange = isAlly ? 6 : 4;
    for (int i = -sightRange; i < sightRange; i++) {
        for (int j = -sightRange; j < sightRange; j++) {
            Vector2Int pos = Vector2Int(gridPosition.x + i, gridPosition.z + j);
            if (grid->isInBounds(pos)) {
                Tile *tile = grid->getTileAt(pos);
                if (tile->unit != nullptr && tile->unit->IsAlly() != isAlly) {
                    enemies.push_back(tile->unit);
                }
            }
        }
    }
    return enemies;
}

Unit *Unit::GetClosestEnemyInSight() {
std::vector<Unit*> enemies = GetEnemiesInSight();
    if (enemies.empty())
        return nullptr;

    std::sort(enemies.begin(), enemies.end(), [this](Unit * enemy, Unit * enemy1){
        return VectorUtils::Distance(this->gridPosition, enemy->gridPosition) < VectorUtils::Distance(this->gridPosition, enemy1->gridPosition);
    });
    return enemies.at(0);
}

Vector2Int Unit::GetDirtiestTileAround() {
    int dirtiestLevel = 0;
    Vector2Int dirtiestTile = gridPosition;
    std::vector<Vector2Int> directions = {Vector2Int(1, 0), Vector2Int(-1, 0), Vector2Int(0, 1), Vector2Int(0, -1), Vector2Int(1, 1), Vector2Int(-1, -1), Vector2Int(1, -1), Vector2Int(-1, 1)};
    //randomize the directions vector
    std::shuffle(directions.begin(), directions.end(), std::mt19937(std::random_device()()));

    for(auto &dir : directions){
        Vector2Int pos = gridPosition + dir;
        if(grid->isInBounds(pos)){
            Tile* tile = grid->getTileAt(pos);
            if(tile->dirtinessLevel > dirtiestLevel){
                dirtiestLevel = tile->dirtinessLevel;
                dirtiestTile = pos;
            }
        }
    }
    return dirtiestTile;
}

