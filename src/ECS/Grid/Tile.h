#ifndef ZTGK_TILE_H
#define ZTGK_TILE_H

#include "Utils/VectorUtils.h"

class Tile {
public:
    Vector2Int index{};
    bool vacant;

    // Constructors
    explicit Tile(Vector2Int index, bool vacant = true);
    Tile(int index_x, int index_z, bool vacant = true);

    Tile() = default;

    // Destructor
    ~Tile();
};

#endif //ZTGK_TILE_H
