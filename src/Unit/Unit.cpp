//
// Created by igork on 22.03.2024.
//

#include "Unit.h"

#include <utility>

Unit::Unit(SystemManager *systemManager, std::string name, Grid *grid, Vector2Int gridPosition) : Entity(systemManager, std::move(name)) {
    this->grid = grid;
    this->gridPosition = gridPosition;

//    StateManager sm = StateManager(this);
//    addComponent(sm);


}
