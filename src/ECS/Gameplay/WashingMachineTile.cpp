//
// Created by igork on 23.05.2024.
//

#include "WashingMachineTile.h"
#include "WashingMachine.h"

WashingMachineTile::WashingMachineTile(WashingMachine *washingMachine, Vector2Int gridPosition, Grid *grid) {
    this->washingMachine = washingMachine;
    this->gridPosition = gridPosition;
    this->grid = grid;
    this->name = "WashingMachineTile " + std::to_string(gridPosition.x) + " " + std::to_string(gridPosition.z);

    washingMachine->addComponent(this);

}
