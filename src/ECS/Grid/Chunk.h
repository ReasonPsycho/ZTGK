//
// Created by redkc on 24/04/2024.
//

#ifndef ZTGK_CHUNK_H
#define ZTGK_CHUNK_H


#include "Tile.h"
#include "ECS/Render/FrustumCulling/BoundingVolume.h"


class Grid;

class Chunk {

public:
     Chunk(Vector2Int index,Grid* grid);
    //number of tiles in the grid
    const int width = 10;
    const int height = 10;
    Vector2Int index{};

    std::vector<std::unique_ptr<WallData>> wallDataArray;


    glm::vec3 chunkRealPosition();
    AABB getBoundingVolume(); //TODO cash it somewhere
    WallData *addWallData(std::unique_ptr<WallData>  wallData);
    void removeWallData(WallData *wallData);
    
    Grid *grid;
};

#endif //ZTGK_CHUNK_H
