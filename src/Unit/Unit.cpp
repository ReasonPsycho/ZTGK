//
// Created by igork on 22.03.2024.
//

#include "Unit.h"

Unit::Unit(SystemManager *systemManager, std::string name, Grid *grid, Vector2Int gridPosition, UnitStats stats, bool isAlly) : Entity(systemManager, std::move(name)) {
    this->grid = grid;
    this->gridPosition = gridPosition;
    this->worldPosition = grid->GridToWorldPosition(gridPosition);
    this->pathfinding = AstarPathfinding(grid);
    this->stats = stats;
    this->isAlly = isAlly;
}

Unit::~Unit() {
    delete currentState;
}

bool Unit::IsAlly() const {
    return isAlly;
}
