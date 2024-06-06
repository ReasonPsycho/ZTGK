//
// Created by redkc on 24/04/2024.
//

#ifndef ZTGK_CHUNK_H
#define ZTGK_CHUNK_H


#include "Tile.h"
#include "ECS/Render/FrustumCulling/BoundingVolume.h"
#include "ECS/Light/Components/PointLight.h"


class Grid;

class Chunk : public Component{

public:
     Chunk(Vector2Int index,Grid* grid,int width,int height);

     //Data
    int width;
    int height;
    bool isVisible;
    int minedTiles;
    int visibleTiles;
    
    PointLight* localLight = nullptr;
    Vector2Int index{};
    
    std::vector<std::unique_ptr<WallData>> wallDataArray;
    std::vector<std::vector<Tile*>> chunkTileArray;

    //Tiles
    Tile *getTileAt(int x, int z);
    Tile *getTileAt(Vector2Int index);

    void setTileAt(int x, int z, Tile *tile);
    void setTileAt(Vector2Int index, Tile *tile);
    void removeTileAt(int x, int z);
    void removeTileAt(Vector2Int index);
    
    void CalculateChunkData();
    glm::vec3 chunkRealPosition();
    AABB getBoundingVolume(); //TODO cash it somewhere
    WallData *addWallData(std::unique_ptr<WallData>  wallData);
    void removeWallData(WallData *wallData);
    
    Grid *grid;
};

#endif //ZTGK_CHUNK_H
