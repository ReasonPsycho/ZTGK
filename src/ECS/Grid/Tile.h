#ifndef ZTGK_TILE_H
#define ZTGK_TILE_H

#include "VectorUtils.h"

class Tile {
public:
    Vector2Int index;
    bool vacant;

    // Constructors
    explicit Tile(Vector2Int index, bool vacant = true) : index(index), vacant(vacant) {}
    Tile(int index_x, int index_z, bool vacant = true) : index(index_x, index_z), vacant(vacant) {}

    Tile() = default;

    // Destructor
    ~Tile();
};

#endif //ZTGK_TILE_H
