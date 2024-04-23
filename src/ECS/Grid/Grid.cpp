//
// Created by igork on 20.03.2024.
//

#include "Grid.h"
#include "ECS/Entity.h"
#include "ECS/Render/Components/Render.h"
#include "ECS/Render/Primitives/Primitives.h"
#include "ECS/Render/Primitives/PBRPrimitives.h"
#include "ECS/Raycasting/CollisionSystem.h"


Grid::Grid(Scene *scene, int width, int height, float tileSize, Vector3 Position) {
    this->name = "Grid";
    this->scene = scene;
    this->width = width;
    this->height = height;
    this->tileSize = tileSize;
    this->Position = Position;
    // center the grid
    offsetX = -width * tileSize / 2.0f;
    offsetZ = -height * tileSize / 2.0f;

    gridArray.resize(width);
    for (int i = 0; i < width; i++) {
        gridArray[i].resize(height);
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            gridArray[i][j] = nullptr;
        }
    }
}

/**
 * @brief Destroys the Grid object.
 *
 * The Grid destructor deletes the gridArray member variable and all of its elements.
 */
Grid::~Grid() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            delete gridArray[i][j];
        }
    }

    delete this;
}

/**
 * @brief Returns the tile at the specified index.
 *
 * The getTileAt function returns a pointer to the Tile object at the specified index in the gridArray.
 *
 * @param x The x-index of the tile.
 * @param z The z-index of the tile.
 * @return Tile* A pointer to the Tile object at the specified index.
 */
Tile *Grid::getTileAt(int x, int z) {
    if( x < width && x >= 0){
        if( z < height && z >= 0) {
            return gridArray[x][z];
        }
    }
    return nullptr;
}

/**
 * @brief Returns the tile at the specified index.
 *
 * The getTileAt function returns a pointer to the Tile object at the specified index in the gridArray.
 *
 * @param index The index of the tile.
 * @return Tile* A pointer to the Tile object at the specified index.
 */
Tile *Grid::getTileAt(Vector2Int index) {
    return gridArray[index.x][index.z];
}


const glm::vec3 Grid::GridToWorldPosition(Vector2Int index) const {

    float worldPosX = Position.x + index.x * tileSize;
    float worldPosY = Position.y;
    float worldPosZ = Position.z + index.z * tileSize;
    return glm::vec3(worldPosX, worldPosY, worldPosZ);}


const glm::vec3 Grid::GridToWorldPosition(int x, int z) const {
    return GridToWorldPosition(Vector2Int(x, z));
}

Vector2Int Grid::WorldToGridPosition(Vector3 position) const {
    // Calculate the offset from the grid's origin
    float offsetX = position.x - Position.x;
    float offsetZ = position.z - Position.z;

    // Calculate the grid index based on the offset and tileSize
    int gridX = static_cast<int>(offsetX / tileSize);
    int gridZ = static_cast<int>(offsetZ / tileSize);

    // Ensure the grid index is within bounds
    if (gridX < 0) gridX = 0;
    if (gridZ < 0) gridZ = 0;
    if (gridX >= width) gridX = width - 1;
    if (gridZ >= height) gridZ = height - 1;

    return {gridX, gridZ};
}

void Grid::showImGuiDetails(Camera *camera) {
    ImGui::PushID(uniqueID);
    if (ImGui::CollapsingHeader("Grid")) {
        ImGui::Text("Width: %d", width);
        ImGui::Text("Height: %d", height);
        ImGui::Text("Tile Size: %f", tileSize);
        ImGui::Text("Offset X: %f", offsetX);
        ImGui::Text("Offset Z: %f", offsetZ);
    }
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            ImGui::PushID(gridArray[i][j]->uniqueID);
            if (ImGui::CollapsingHeader(("Tile " + std::to_string(i) + " " + std::to_string(j)).c_str())) {
                gridArray[i][j]->showImGuiDetails(camera);
                glm::vec3 worldPos = GridToWorldPosition(i, j);
                ImGui::Text("World Position: (%f, %f, %f)", worldPos.x, worldPos.y, worldPos.z);

            }
            ImGui::PopID();
        }
    }

    ImGui::PopID();

}

void Grid::LoadTileEntities(float scale, CollisionSystem *collisionSystem) {
    Entity *gridEntity = scene->addEntity("Grid Entity");
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Entity *tileEntity = scene->addEntity(gridEntity, "Tile " + std::to_string(i) + " " + std::to_string(j));
            tileEntity->addComponent(std::make_unique<Tile>(i, j));
            tileEntity->transform.setLocalPosition(GridToWorldPosition(i, j));
            tileEntity->transform.setLocalScale(glm::vec3(scale, scale, scale));

            if (i >= width / 4 && i < (width - width / 4) && j >= height / 4 && j < (height - height / 4)) {
                tileEntity->getComponent<Tile>()->isFloor = true;

            } else {
                tileEntity->getComponent<Tile>()->isFloor = false;
                tileEntity->getComponent<Tile>()->vacant = false;
            }

            tileEntity->updateSelfAndChild();

            tileEntity->addComponent(
                    std::make_unique<BoxCollider>(tileEntity, glm::vec3(0.5, 0.5, 0.5), collisionSystem));
            tileEntity->getComponent<BoxCollider>()->center =
                    tileEntity->transform.getGlobalPosition() + glm::vec3(0, 0, 0.5);
        }
    }

    SetUpWallData();
}

void Grid::addComponent(void *component) {
    auto c = static_cast<Component *>(component);
    Tile * tile = dynamic_cast<Tile *>(c);
    gridArray[tile->index.x][tile->index.z] = tile;
}

void Grid::removeComponent(void *component) {
    auto c = static_cast<Component *>(component);
    Tile * tile = dynamic_cast<Tile *>(c);
    gridArray[tile->index.x][tile->index.z] = nullptr;
}

const std::type_index *Grid::getComponentTypes() {
    return componentTypes.data();
}

int Grid::getNumComponentTypes() {
    return 1;
}

Grid::Grid(Grid *grid) {
    this->name = "Grid";
    this->scene = grid->scene;
    this->width = grid->width;
    this->height = grid->height;
    this->tileSize = grid->tileSize;
    this->Position = grid->Position;
    this->offsetX = grid->offsetX;
    this->offsetZ = grid->offsetZ;
    this->gridArray = grid->gridArray;

}

void Grid::SetUpWallData() {
    float translateLength = tileSize / 2.0f;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Tile *currentTile = getTileAt(i, j);
            if(currentTile->isFloor){
                currentTile->walls.clear();
                glm::mat4x4 floorMatrix = currentTile->getEntity()->transform.getModelMatrix();
                floorMatrix = glm::translate(floorMatrix,glm::vec3(0,-translateLength,0));
                floorMatrix = glm::rotate(floorMatrix,glm::radians(90.0f),glm::vec3 (1,0,0));
                currentTile->walls.push_back(WallData(floorMatrix));
            }else{
                
                
                Tile *northNeighbour = getTileAt(i + 1, j);
                if (northNeighbour == nullptr || northNeighbour->isFloor){
                    glm::mat4x4 northMatrix = currentTile->getEntity()->transform.getModelMatrix();
                    northMatrix = glm::translate(northMatrix,glm::vec3(translateLength,0,0));
                    northMatrix = glm::rotate(northMatrix,glm::radians(-90.0f),glm::vec3 (0,1,0));
                    currentTile->walls.push_back(WallData(northMatrix));
                }
                    
                 
                Tile *southNeighbour = getTileAt(i - 1, j);
                if (southNeighbour == nullptr || southNeighbour->isFloor){
                    glm::mat4x4 southMatrix = currentTile->getEntity()->transform.getModelMatrix();
                    southMatrix = glm::translate(southMatrix,glm::vec3(-translateLength,0,0));
                    southMatrix = glm::rotate(southMatrix,glm::radians(90.0f),glm::vec3 (0,1,0));
                    currentTile->walls.push_back(WallData(southMatrix));
                }
                Tile *eastNeighbour = getTileAt(i, j + 1);
                if (eastNeighbour == nullptr || eastNeighbour->isFloor){
                    glm::mat4x4 eastMatrix = currentTile->getEntity()->transform.getModelMatrix();
                    eastMatrix = glm::translate(eastMatrix,glm::vec3(0,0,translateLength));
                    eastMatrix = glm::rotate(eastMatrix,glm::radians(90.0f),glm::vec3 (0,0,1));
                    currentTile->walls.push_back(WallData(eastMatrix));
                }
                
                Tile *westNeighbour = getTileAt(i, j - 1);
                if (westNeighbour == nullptr || westNeighbour->isFloor){
                    glm::mat4x4 westMatrix = currentTile->getEntity()->transform.getModelMatrix();
                    westMatrix = glm::translate(westMatrix,glm::vec3(0,0,-translateLength));
                  //  westMatrix = glm::rotate(westMatrix,glm::radians(-90.0f),glm::vec3 (1,0,0));
                    currentTile->walls.push_back(WallData(westMatrix));
                }
              
                glm::mat4x4 topMatrix = currentTile->getEntity()->transform.getModelMatrix();
                topMatrix = glm::translate(topMatrix,glm::vec3(0,translateLength,0));
                topMatrix = glm::rotate(topMatrix,glm::radians(90.0f),glm::vec3 (1,0,0));
                currentTile->walls.push_back(WallData(topMatrix));
                 
            }
        }
    }
}



