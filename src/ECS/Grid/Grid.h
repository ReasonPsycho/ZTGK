//
// Created by igork on 20.03.2024.
//

#ifndef ZTGK_GRID_H
#define ZTGK_GRID_H


#include <vector>
#include "Tile.h"
#include "ECS/Component.h"
#include "ECS/Utils/VectorUtils.h"
#include "ECS/Scene.h"
#include "ECS/Render/ModelLoading/Model.h"


class Grid : public Component{
public:
    Entity* entity;
    //number of tiles in the grid
    int width;
    int height;

    //size of the tiles
    float tileSize;

    //2D array of tiles
    std::vector<std::vector<Tile*>> gridArray;

    // Constructor
    Grid() = default;
    Grid(int width, int height, float tileSize, Entity* parentEntity);

    // Destructor
    ~Grid();

    void showImGuiDetails(Camera *camera) override;

    //get the tile at a specific index
    Tile* getTileAt(int x, int z);
    Tile* getTileAt(Vector2Int index);

    [[nodiscard]] Vector3 GridToWorldPosition(Vector2Int index) const;
    [[nodiscard]] Vector3 GridToWorldPosition(int x, int z) const;

    [[nodiscard]] Vector2Int WorldToGridPosition(Vector3 position) const;
  
    void RenderTiles(Scene* scene, float scale, Model* tileModel);
private:
    float offsetX = 0;
    float offsetZ = 0;
};


#endif //ZTGK_GRID_H
