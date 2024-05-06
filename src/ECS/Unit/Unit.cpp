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

const UnitStats Unit::ALLY_BASE = {
        .max_hp = 100,
        .hp = 100,
        .added = {}
};

const UnitStats Unit::ENEMY_BASE = {
        .max_hp = 100,
        .hp = 100,
        .added = {}
};

Unit::Unit(std::string name, Grid *grid, Vector2Int gridPosition, UnitStats baseStats, bool isAlly, UnitSystem* unitSystem) {
    this->name = std::move(name);
    this->equipment = UnitEquipment();
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
    delete currentState;
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

    ImGui::Text("Unit: %s", name.c_str());
    ImGui::Text("Grid Position: (%d, %d)", gridPosition.x, gridPosition.z);
    ImGui::Text("World Position: (%f, %f, %f)", worldPosition.x, worldPosition.y, worldPosition.z);
    ImGui::Text("Ally: %s", isAlly ? "true" : "false");
    ImGui::Text("Selected: %s", isSelected ? "true" : "false");
    ImGui::Text("HP %f / %f (%f + %f)", stats.hp, stats.max_hp + stats.added.max_hp, stats.max_hp, stats.added.max_hp);
    if (ImGui::CollapsingHeader("Added stats:")) {
        stats.added.imgui_preview();
    }

}

void Unit::UpdateImpl() {


    if(hasMovementTarget){
        if(!grid->getTileAt(movementTarget)->vacant()){
            movementTarget = pathfinding.GetNearestVacantTile(movementTarget, gridPosition);
            pathfinding.FindPath(gridPosition, movementTarget);
        }
    }

    gridPosition = grid->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(worldPosition));

    combatTarget = findEnemy();
    if(combatTarget != nullptr){
        hasCombatTarget = true;
    }
    else{
        hasCombatTarget = false;
    }

    if (gridPosition != previousGridPosition) {
        grid->getTileAt(previousGridPosition)->state = FLOOR;
        grid->getTileAt(gridPosition)->state = UNIT;
        grid->getTileAt(previousGridPosition)->unit = nullptr;
        grid->getTileAt(gridPosition)->unit = this;
    }

    getEntity()->transform.setLocalPosition(worldPosition);
    if(currentRotation > rotation){
        currentRotation -= 0.1f;
    }
    if(currentRotation < rotation){
        currentRotation += 0.1f;
    }
    getEntity()->transform.setLocalRotation(glm::vec3(0, currentRotation, 0));

    previousGridPosition = gridPosition;

    if (equipment.item0->cd_sec > 0)
        equipment.item0->cd_sec -= Time::Instance().DeltaTime();
    if (equipment.item1 != nullptr && equipment.item1->cd_sec > 0)
        equipment.item1->cd_sec -= Time::Instance().DeltaTime();
    if (equipment.item2 != nullptr && equipment.item2->cd_sec > 0)
        equipment.item2->cd_sec -= Time::Instance().DeltaTime();
    if (equipment.cd_between_sec > 0)
        equipment.cd_between_sec -= Time::Instance().DeltaTime();
}

Unit *Unit::findEnemy() {
    std::vector<Unit*> enemies;

    if (equipment.use_default()) {
        auto found = equipment.rangeEff0.find_enemies({gridPosition.x, gridPosition.z});
        enemies.insert(enemies.end(), found.begin(), found.end());
    } else {
        if (equipment.item1 != nullptr && equipment.item1->offensive) {
            auto found = equipment.rangeEff1.find_enemies({gridPosition.x, gridPosition.z});
            enemies.insert(enemies.end(), found.begin(), found.end());
        }
        if (equipment.item2 != nullptr && equipment.item2->offensive) {
            auto found = equipment.rangeEff2.find_enemies({gridPosition.x, gridPosition.z});
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
//    int sightRange = 5 + added.range;
//    for (int i = -sightRange; i < sightRange; i++) {
//        for (int j = -sightRange; j < sightRange; j++) {
//            Vector2Int pos = Vector2Int(gridPosition.x + i, gridPosition.z + j);
//            if (grid->isInBounds(pos)) {
//                Tile *tile = grid->getTileAt(pos);
//                if (tile->unit != nullptr && tile->unit->IsAlly() != isAlly) {
//                    return tile->unit;
//                }
//            }
//        }
//    }
//    return nullptr;
}


bool Unit::canFindPathToTarget(Vector2Int target) {
    pathfinding.FindPath(gridPosition, target);
    return !pathfinding.path.empty();
}




void Unit::serializer_init(Grid * pGrid) {
    auto playerUnit = getEntity();
    auto stateManager = new StateManager(playerUnit->getComponent<Unit>());
    stateManager->currentState = new IdleState(pGrid);
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
    playerUnit->addComponent(make_unique<BoxCollider>(playerUnit, glm::vec3(2, 2, 2), ztgk::game::scene->systemManager.getSystem<CollisionSystem>()));
    playerUnit->getComponent<BoxCollider>()->center = playerUnit->transform.getGlobalPosition() + glm::vec3(0, 0, 0.5);
    playerUnit->addComponent(make_unique<Unit>());
    return playerUnit;
}

