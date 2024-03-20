//
// Created by igork on 20.03.2024.
//

#include "Tile.h"


Tile::~Tile() {
    vacant = true;
    delete this;
}
