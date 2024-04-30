//
// Created by igork on 22.03.2024.
//

#include "Unit.h"

#include <utility>
#include "UnitSystem.h"
#include "ECS/Utils/Time.h"

Unit::Unit(std::string name, Grid *grid, Vector2Int gridPosition, UnitStats baseStats, bool isAlly, UnitSystem* unitSystem) {
    this->name = std::move(name);
    this->equipment = UnitEquipment();
    this->grid = grid;
    this->gridPosition = gridPosition;
    this->worldPosition = grid->GridToWorldPosition(gridPosition);
    this->pathfinding = AstarPathfinding(grid);
    this->baseStats = baseStats;
    this->isAlly = isAlly;
    this->previousGridPosition = gridPosition;
    grid->getTileAt(gridPosition)->vacant = false;
    grid->getTileAt(gridPosition)->unit = this;
    UpdateStats();

    //unitSystem->addComponent(this);
}

Unit::~Unit() {
    delete currentState;
}

bool Unit::IsAlly() const {
    return isAlly;
}

void Unit::EquipItem(Item item, short slot) {
    // assigning address of copied item, use reference or pointer
    equipment.equipItem(&item, slot);
    UpdateStats();
}

void Unit::UnequipItem(short slot) {
    equipment.unequipItem(slot);
    UpdateStats();
}

void Unit::UpdateStats() {
    stats = baseStats;
    if(equipment.item1 != nullptr){
        stats.health += equipment.item1->stats.addHealth;
        stats.attackDamage += equipment.item1->stats.addAttackDamage;
        stats.attackSpeed += equipment.item1->stats.addAttackSpeed;
        stats.movementSpeed += equipment.item1->stats.addMovementSpeed;
        stats.range += equipment.item1->stats.addRange;
    }
    if(equipment.item2 != nullptr){
        stats.health += equipment.item2->stats.addHealth;
        stats.attackDamage += equipment.item2->stats.addAttackDamage;
        stats.attackSpeed += equipment.item2->stats.addAttackSpeed;
        stats.movementSpeed += equipment.item2->stats.addMovementSpeed;
        stats.range += equipment.item2->stats.addRange;
    }
}

UnitStats Unit::GetBaseStats() {
    return this->baseStats;
}

void Unit::showImGuiDetails(Camera *camera) {

    ImGui::Text("Unit: %s", name.c_str());
    ImGui::Text("Grid Position: (%d, %d)", gridPosition.x, gridPosition.z);
    ImGui::Text("World Position: (%f, %f, %f)", worldPosition.x, worldPosition.y, worldPosition.z);
    ImGui::Text("Health: %f", stats.health);
    ImGui::Text("Attack Damage: %f", stats.attackDamage);
    ImGui::Text("Attack Speed: %f", stats.attackSpeed);
    ImGui::Text("Movement Speed: %f", stats.movementSpeed);
    ImGui::Text("Range: %f", stats.range);
    ImGui::Text("Ally: %s", isAlly ? "true" : "false");
    ImGui::Text("Selected: %s", isSelected ? "true" : "false");


}

void Unit::Update() {


    if(hasMovementTarget){
        if(!grid->getTileAt(movementTarget)->vacant){
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
        grid->getTileAt(previousGridPosition)->vacant = true;
        grid->getTileAt(gridPosition)->vacant = false;
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

    attackCooldown += Time::Instance().DeltaTime();
}

Unit *Unit::findEnemy() {
    int sightRange = 5 + stats.range;
    for (int i = -sightRange; i < sightRange; i++) {
        for (int j = -sightRange; j < sightRange; j++) {
            Vector2Int pos = Vector2Int(gridPosition.x + i, gridPosition.z + j);
            if (grid->isInBounds(pos)) {
                Tile *tile = grid->getTileAt(pos);
                if (tile->unit != nullptr && tile->unit->IsAlly() != isAlly) {
                    return tile->unit;
                }
            }
        }
    }
    return nullptr;
}

bool Unit::canFindPathToTarget(Vector2Int target) {
    pathfinding.FindPath(gridPosition, target);
    return !pathfinding.path.empty();
}



