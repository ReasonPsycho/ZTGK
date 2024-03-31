//
// Created by igork on 22.03.2024.
//

#include "Unit.h"


Unit::Unit(SystemManager *systemManager, std::string name, Grid *grid, Vector2Int gridPosition, UnitStats baseStats, bool isAlly) :Entity(scene, std::move(name)) {
    this->equipment = UnitEquipment();
    this->grid = grid;
    this->gridPosition = gridPosition;
    this->worldPosition = grid->GridToWorldPosition(gridPosition);
    this->pathfinding = AstarPathfinding(grid);
    this->baseStats = baseStats;
    this->isAlly = isAlly;

    UpdateStats();
}

Unit::~Unit() {
    delete currentState;
}

bool Unit::IsAlly() const {
    return isAlly;
}

void Unit::EquipItem(Item item, short slot) {
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
