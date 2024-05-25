//
// Created by igork on 23.05.2024.
//

#include "Pranium.h"

Pranium::Pranium(float timeToMine, Vector2Int gridPosition, Grid *grid) : IMineable(timeToMine, gridPosition, grid) {
    name = "Pranium";

}

void Pranium::onMine(Unit *unit) {

}

void Pranium::onMined(Unit *unit) {

}
