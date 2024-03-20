//
// Created by igork on 20.03.2024.
//

#ifndef ZTGK_GRID_H
#define ZTGK_GRID_H


#include <vector>
#include "Tile.h"
#include "ECS/Component.h"
#include "VectorUtils.h"


class Grid : public Component{
public:
    Entity* entity;
    //number of tiles in the grid
    int width;
    int height;

    //size of the tiles
    float tileSize;

    //2D array of tiles
    std::vector<std::vector<Tile>> gridArray;

    // Constructor
    Grid(int width, int height, float tileSize);

    // Destructor
    ~Grid() override;


    //get the tile at a specific index
    Tile* getTileAt(int x, int z);
    Tile* getTileAt(Vector2Int index);

    [[nodiscard]] Vector3 GridToWorldPosition(Vector2Int index) const;
    [[nodiscard]] Vector3 GridToWorldPosition(int x, int z) const;

    [[nodiscard]] Vector2Int WorldToGridPosition(Vector3 position) const;

private:
    float offsetX = 0;
    float offsetZ = 0;
};


#endif //ZTGK_GRID_H
