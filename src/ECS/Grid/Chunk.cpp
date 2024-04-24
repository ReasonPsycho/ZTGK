//
// Created by redkc on 24/04/2024.
//


#include "Grid.h"
#include "Chunk.h"

WallData* Chunk::addWallData(WallData wallData) {
    // Push the WallData to the vector
    this->wallDataArray.push_back(wallData);

    // Return the pointer to the last WallData object pushed into the vector
    return &this->wallDataArray.back();
}

void Chunk::removeWallData(WallData* wallData) {
    // Iterate through the wallDataArray vector
    for (auto it = this->wallDataArray.begin(); it != this->wallDataArray.end(); ++it) {
        if (&(*it) == wallData) {
            // Remove the WallData element
            this->wallDataArray.erase(it);
            break;
        }
    }
}


Chunk::Chunk(Vector2Int index, Grid *grid) :index(index),grid(grid){

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
