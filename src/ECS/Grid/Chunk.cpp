// 
// Created by redkc on 24/04/2024. 
// 
 
 
#include "Grid.h" 
#include "Chunk.h" 
 
WallData* Chunk::addWallData(std::unique_ptr<WallData> wallData) { 
    // Push the WallData to the vector 
     
    this->wallDataArray.push_back(std::move(wallData)); 
    // Return the pointer to the last WallData object pushed into the vector 
    return this->wallDataArray.back().get(); 
} 
 
void Chunk::removeWallData(WallData* wallData) { 
    auto it = std::find_if(wallDataArray.begin(), wallDataArray.end(), [&](const std::unique_ptr<WallData>& ptr) { 
        return ptr.get() == wallData; 
    }); 
 
    if (it != wallDataArray.end()) { 
        wallDataArray.erase(it); 
    } 
} 
 
 
 
glm::vec3 Chunk::chunkRealPosition() { 
    return glm::vec3 ( 
    grid->Position.x + (index.x * 10 +5)  * grid->tileSize, 
    grid->Position.y, 
    grid->Position.z + (index.z * 10 +5) * grid->tileSize 
    ); 
} 
 
AABB Chunk::getBoundingVolume() { 
    return AABB(chunkRealPosition(), width * grid->tileSize,2,height * grid->tileSize ); 
} 
 
Chunk::Chunk(Vector2Int index, Grid *grid, int width, int height) :index(index),grid(grid),width(width),height(height) { 
    name = "Chunk"; 
 
    chunkTileArray.resize(width); 
    for (int i = 0; i < width; i++) { 
        chunkTileArray[i].resize(height); 
    } 
 
    for (int i = 0; i < width; i++) { 
        for (int j = 0; j < height; j++) { 
            chunkTileArray[i][j] = nullptr; 
        } 
    } 
} 
 
Tile *Chunk::getTileAt(int x, int z) { 
    return chunkTileArray[x][z]; 
} 
 
Tile *Chunk::getTileAt(Vector2Int index) { 
    return  chunkTileArray[index.x][index.z]; 
} 
 
void Chunk::setTileAt(int x, int z, Tile *tile) { 
    chunkTileArray[x][z] = tile; 
} 
 
void Chunk::setTileAt(Vector2Int index, Tile *tile) { 
    chunkTileArray[index.x][index.z] = tile; 
} 
 
void Chunk::removeTileAt(Vector2Int index) { 
    chunkTileArray[index.x][index.z]->Remove(); 
} 
 
void Chunk::removeTileAt(int x, int z) { 
//    chunkTileArray[x][z]->Remove(); 
    chunkTileArray[x][z] = nullptr; 
} 
 
void Chunk::CalculateChunkData() { 
    minedTiles = 0; 
    for (int x = 0; x < width; ++x) { 
        for (int y = 0; y < height; ++y) { 
            TileState state = chunkTileArray[x][y]->state; 
            if (state != WALL && state != ORE){ 
                minedTiles++; 
            } 
        }    
    } 
    isAccessibleFromCore = true; // TODO do here A* 
} 
 
