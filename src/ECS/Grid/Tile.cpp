//
// Created by igork on 20.03.2024.
//

#include "Tile.h"


Tile::~Tile() {
    vacant = true;
    delete this;
}

Tile::Tile(Vector2Int index, bool vacant) {
    this->index = index;
    this->vacant = vacant;
}

Tile::Tile(int index_x, int index_z, bool vacant) {
    this->index = Vector2Int(index_x, index_z);
    this->vacant = vacant;
}


