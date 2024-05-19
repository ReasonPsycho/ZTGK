//
// Created by igork on 20.03.2024.
//

#include "Grid.h"
#include "ECS/Entity.h"
#include "ECS/Render/Components/Render.h"
#include "ECS/Render/Primitives/Primitives.h"
#include "ECS/Raycasting/CollisionSystem.h"
#include "ECS/Unit/Mining/IMineable.h"
#include "ECS/Utils/Globals.h"
#include "tracy/Tracy.hpp"
#include "ECS/Unit/Mining/MineableChest.h"
#include "ECS/Light/Components/PointLight.h"

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

    int chunkSize = CalculateOptimalChunkSize(width,height);
    chunkHeight = chunkSize;
    chunkWidth = chunkHeight;

    for (int i = 0; i < width / chunkWidth; i++) {
        std::vector<Chunk*> chunkLine;    // Create a new line
        for (int j = 0; j < height / chunkHeight; j++) {
            chunkLine.push_back(nullptr);  // Populate the line
        }
        chunkArray.push_back(std::move(chunkLine));  // Add the line to the array
    }
}

/**
 * @brief Destroys the Grid object.
 *
 * The Grid destructor deletes the gridArray member variable and all of its elements.
 */
Grid::~Grid() {

}

void Grid::Clear() {
    gridEntity->Destroy();
}


void Grid::reinitWithSize(glm::ivec2 size) {
    Clear();
    width = size.x;
    height = size.y;
    int chunkSize = CalculateOptimalChunkSize(size.x,size.x);
    chunkHeight = chunkSize;
    chunkWidth = chunkHeight;

    for (int i = 0; i < width / chunkWidth; i++) {
        std::vector<Chunk*> chunkLine;    // Create a new line
        for (int j = 0; j < height / chunkHeight; j++) {
            chunkLine.push_back(nullptr);  // Populate the line
        }
        chunkArray.push_back(std::move(chunkLine));  // Add the line to the array
    }
    
    auto entity = std::find_if(scene->getChildren().begin(), scene->getChildren().end(),
                               [this](std::unique_ptr<Entity> &child) { return child->uniqueID == entityId; });
    if (entity != scene->getChildren().end())
        (*entity)->Destroy();

    GenerateTileEntities(1.0f);
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
    if (x < width && x >= 0) {
        if (z < height && z >= 0) {
            return chunkArray[x/chunkWidth][z/chunkHeight]->getTileAt(x%chunkWidth,z%chunkHeight);
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

    if (index.x < width && index.x >= 0) {
        if (index.z < height && index.z >= 0) {
            return chunkArray[index.x/chunkWidth][index.z/chunkHeight]->getTileAt(index.x%chunkWidth,index.z%chunkHeight);
        }
    }
    return nullptr;
}


const glm::vec3 Grid::GridToWorldPosition(Vector2Int index) const {

    float worldPosX = Position.x + index.x * tileSize + tileSize/2;
    float worldPosY = Position.y;
    float worldPosZ = Position.z + index.z * tileSize + tileSize/2;
    return glm::vec3(worldPosX, worldPosY, worldPosZ);
}


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

void Grid::showImGuiDetailsImpl(Camera *camera) {
    ZoneScopedN("ShowImGuiDetails Grid");

    // Display each variable as text:
    ImGui::Text("Width: %d", width);
    ImGui::Text("Height: %d", height);
    ImGui::Text("Chunk Width: %d", chunkWidth);
    ImGui::Text("Chunk Height: %d", chunkHeight);
    ImGui::Text("Tile Size: %.2f", tileSize);
}

void Grid::GenerateTileEntities(float scale) {
    gridEntity = scene->addEntity("Grid Entity");
    entityId = gridEntity->uniqueID;
    gridEntity->updateChildren = false;
    for (int i = 0; i < width /chunkWidth; i++) {
        for (int j = 0; j < height/chunkHeight; j++) {
            Entity *chunkEntity = scene->addEntity(gridEntity, "Chunk " + std::to_string(i) + " " + std::to_string(j));
            chunkEntity->addComponent(make_unique<Chunk>(Vector2Int(i, j), this,chunkWidth,chunkHeight));
            chunkArray[i][j] = chunkEntity->getComponent<Chunk>();
            chunkEntity->transform.setLocalPosition(glm::vec3(i * chunkWidth * tileSize, 0, j * chunkHeight * tileSize));
            chunkEntity->forceUpdateSelfAndChild();
            chunkEntity->addComponent(std::make_unique<BoxCollider>(chunkEntity, glm::vec3(chunkWidth*tileSize ,0.8,chunkHeight*tileSize),CollisionType::CHUNK));
            chunkEntity->getComponent<BoxCollider>()->setCenter(chunkEntity->transform.getGlobalPosition() + glm::vec3(chunkWidth, 0, chunkHeight));
            chunkEntity->getComponent<BoxCollider>()->size = glm::vec3 (10,1,10);
            for (int x = 0; x < chunkWidth; ++x) {
                for (int z = 0; z < chunkHeight; ++z) {
                    Entity *tileEntity = scene->addEntity(chunkEntity, "Tile " + std::to_string(x) + " " + std::to_string(z));
                    tileEntity->addComponent(std::make_unique<Tile>(i * chunkWidth + x, j * chunkHeight + z, chunkEntity->getComponent<Chunk>()));
                    tileEntity->transform.setLocalPosition(glm::vec3 (x * tileSize + tileSize/2,0, z * tileSize+ tileSize/2)); //TODO find where it is
                    tileEntity->transform.setLocalScale(glm::vec3(scale, scale, scale));

                    tileEntity->forceUpdateSelfAndChild();
                    tileEntity->addComponent(
                            std::make_unique<BoxCollider>(tileEntity, glm::vec4(1, 0.2, 1,1),CollisionType::TILE));
                    tileEntity->getComponent<BoxCollider>()->setCenter(
                            tileEntity->transform.getGlobalPosition() + glm::vec3(0, -10, 0.5));
                }
            }
        }
    }
    gridEntity->forceUpdateSelfAndChild();
}

void Grid::InitializeTileEntities() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            auto tile = getTileAt(i, j);

            switch (tile->state) {
                // todo these once relevant
                // stateData will be set by the serializer, here init components & stuff as necessary from the loaded state
                default:
                case FLOOR:
                case ORE:
                case CORE:
                case UNIT:
                case state_count:   // keep this one empty or signal error, this is unreachable
                    break;
                case CHEST:
                    // todo item type id
                    tile->getEntity()->addComponent(std::make_unique<MineableChest>(Vector2Int(i, j), this, 1));
                    tile->getEntity()->addComponent(std::make_unique<PointLight>());
                    break;
                case WALL:
                    tile->getEntity()->addComponent(std::make_unique<IMineable>(1.0f, Vector2Int(i, j), this));
                    break;
            }
        }
    }
}

void Grid::LoadTileEntities(float scale) {
    gridEntity = scene->addEntity("Grid Entity");
    entityId = gridEntity->uniqueID;
    gridEntity->updateChildren = false;
    for (int i = 0; i < width /chunkWidth; i++) {
        for (int j = 0; j < height/chunkHeight; j++) {
            Entity *chunkEntity = scene->addEntity(gridEntity, "Chunk " + std::to_string(i) + " " + std::to_string(j));
            chunkEntity->addComponent(make_unique<Chunk>(Vector2Int(i, j), this,chunkWidth,chunkHeight));
            chunkArray[i][j] = chunkEntity->getComponent<Chunk>();
            chunkEntity->transform.setLocalPosition(glm::vec3(i * chunkWidth * tileSize, 0, j * chunkHeight * tileSize));
            chunkEntity->forceUpdateSelfAndChild();
            chunkEntity->addComponent(std::make_unique<BoxCollider>(chunkEntity, glm::vec3(chunkWidth*tileSize ,0.8,chunkHeight*tileSize),CollisionType::CHUNK));
            chunkEntity->getComponent<BoxCollider>()->setCenter(chunkEntity->transform.getGlobalPosition() + glm::vec3(chunkWidth, 0, chunkHeight) - glm::vec3(0,0,0));
            chunkEntity->getComponent<BoxCollider>()->size = glm::vec3 (10,1,10);
            chunkEntity->getComponent<BoxCollider>()->coordsToExcludeFromUpdate = "xyz";
            for (int x = 0; x < chunkWidth; ++x) {
                for (int z = 0; z < chunkHeight; ++z) {
                    Entity *tileEntity = scene->addEntity(chunkEntity, "Tile " + std::to_string(x) + " " + std::to_string(z));
                    tileEntity->addComponent(std::make_unique<Tile>(i * chunkWidth + x, j * chunkHeight + z, chunkEntity->getComponent<Chunk>()));
                    tileEntity->transform.setLocalPosition(glm::vec3 (x * tileSize + tileSize/2,0, z * tileSize+ tileSize/2)); //TODO find where it is 
                    tileEntity->transform.setLocalScale(glm::vec3(scale, scale, scale));

                    if ((i >= chunkWidth / 4 && i < (chunkWidth - chunkWidth / 4) && j >= chunkHeight / 4 && j < (chunkHeight - chunkHeight / 4)) && (x * i != 40 || z * j != 40 )) {
                        tileEntity->getComponent<Tile>()->state = FLOOR;

                    } else {
                        tileEntity->getComponent<Tile>()->state = WALL;
                        tileEntity->addComponent(std::make_unique<IMineable>(1.0f, tileEntity->getComponent<Tile>()->index , this));

                    }
                    
                    tileEntity->forceUpdateSelfAndChild();
                    tileEntity->addComponent(
                            std::make_unique<BoxCollider>(tileEntity, glm::vec4(1, 1, 1,1),CollisionType::TILE));
                    tileEntity->getComponent<BoxCollider>()->setCenter(
                            tileEntity->transform.getGlobalPosition() + glm::vec3(0, tileEntity->getComponent<Tile>()->state == FLOOR ? -2 : 0, 0));
                }
            }
        }
    }
    gridEntity->forceUpdateSelfAndChild();

    SetUpWalls();
}



void Grid::addComponent(void *component) {
    auto c = static_cast<Component *>(component);
    Tile *tile = dynamic_cast<Tile *>(c);
    setTileAt (tile->index,tile);
}

void Grid::removeComponent(void *component) {
    auto c = static_cast<Component *>(component);
    Tile *tile = dynamic_cast<Tile *>(c);
    removeTileAt(tile->index);
}

const std::type_index *Grid::getComponentTypes() {
    return componentTypes.data();
}

int Grid::getNumComponentTypes() {
    return 1;
}

void Grid::SetUpWalls() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Tile *currentTile = getTileAt(i, j);
            if (currentTile != nullptr)
                SetUpWall(currentTile);
        }
    }
}

void Grid::SetUpWall(Tile *tile) {
    // todo handle core, ore, etc. states with different models/textures or render as floor and create entity (as is now)

    Chunk *wallChunk = getChunkAt(tile->index);
    float translateLength = tileSize / 2.0f;
    bool isDiagonal = ((tile->index.x + tile->index.z) % 2 == 0);
    ClearWall(tile);
    bool isSurrounded = true;
    if (tile->state != WALL) {
        glm::mat4x4 floorMatrix = tile->getEntity()->transform.getModelMatrix();
        floorMatrix = glm::translate(floorMatrix, glm::vec3(0, -translateLength, 0));
        floorMatrix = glm::rotate(floorMatrix, glm::radians(-90.0f), glm::vec3(1, 0, 0));
        tile->walls.push_back(
                wallChunk->addWallData(make_unique<WallData>(floorMatrix, 0, 0, 0, 0,(isDiagonal ? 1 : 2),(isDiagonal ? 1 : 2),0,(isDiagonal ? 1 : 2))));
    } else if (tile->state == WALL) {
        Tile *northNeighbour = getTileAt(tile->index.x + 1, tile->index.z);
        if (northNeighbour == nullptr || northNeighbour->state != WALL) {
            glm::mat4x4 northMatrix = tile->getEntity()->transform.getModelMatrix();
            northMatrix = glm::translate(northMatrix, glm::vec3(translateLength, 0, 0));
            northMatrix = glm::rotate(northMatrix, glm::radians(90.0f), glm::vec3(0, 1, 0));
            tile->walls.push_back(wallChunk->addWallData(make_unique<WallData>(northMatrix, 2, 0, 0, 0,0,0,0,0)));
            isSurrounded = false;
        }

        Tile *southNeighbour = getTileAt(tile->index.x - 1, tile->index.z);
        if (southNeighbour == nullptr || southNeighbour->state != WALL) {
            glm::mat4x4 southMatrix = tile->getEntity()->transform.getModelMatrix();
            southMatrix = glm::translate(southMatrix, glm::vec3(-translateLength, 0, 0));
            southMatrix = glm::rotate(southMatrix, glm::radians(-90.0f), glm::vec3(0, 1, 0));
            tile->walls.push_back(wallChunk->addWallData(make_unique<WallData>(southMatrix, 2, 0, 0, 0,0,0,0,0)));
            isSurrounded = false;
        }

        Tile *eastNeighbour = getTileAt(tile->index.x, tile->index.z + 1);
        if (eastNeighbour == nullptr || eastNeighbour->state != WALL) {
            glm::mat4x4 eastMatrix = tile->getEntity()->transform.getModelMatrix();
            eastMatrix = glm::translate(eastMatrix, glm::vec3(0, 0, translateLength));
            eastMatrix = glm::rotate(eastMatrix, glm::radians(-90.0f), glm::vec3(0, 0, 1));
            tile->walls.push_back(wallChunk->addWallData(make_unique<WallData>(eastMatrix, 2, 0, 0, 0,0,0,0,0)));
            isSurrounded = false;
        }

        Tile *westNeighbour = getTileAt(tile->index.x, tile->index.z - 1);
        if (westNeighbour == nullptr || westNeighbour->state != WALL) {
            glm::mat4x4 westMatrix = tile->getEntity()->transform.getModelMatrix();
            westMatrix = glm::translate(westMatrix, glm::vec3(0, 0, -translateLength));
              westMatrix = glm::rotate(westMatrix,glm::radians(180.0f),glm::vec3 (1,0,0));
            tile->walls.push_back(wallChunk->addWallData(make_unique<WallData>(westMatrix, 2, 0, 0, 0,0,0,0,0)));
            isSurrounded = false;
        }

        glm::mat4x4 topMatrix = tile->getEntity()->transform.getModelMatrix();
        topMatrix = glm::translate(topMatrix, glm::vec3(0, translateLength, 0));
        topMatrix = glm::rotate(topMatrix, glm::radians(-90.0f), glm::vec3(1, 0, 0));
        tile->walls.push_back(
                wallChunk->addWallData(make_unique<WallData>(topMatrix, 2, (isSurrounded ? 1 : 0), 0, 0,0,0,0,0)));
    }
}

void Grid::DestroyWallsOnTile(Vector2Int tileIndex) {
    Tile *currentTile = getTileAt(tileIndex);
    currentTile->state = FLOOR;
    vector<Tile *> neighbours;

    neighbours.push_back(getTileAt(tileIndex.x + 1, tileIndex.z));
    neighbours.push_back(getTileAt(tileIndex.x - 1, tileIndex.z));
    neighbours.push_back(getTileAt(tileIndex.x, tileIndex.z + 1));
    neighbours.push_back(getTileAt(tileIndex.x, tileIndex.z - 1));
    SetUpWall(currentTile);
    for (Tile *neigh: neighbours) {
        if (neigh != nullptr)
            SetUpWall(neigh);
    }

}


Chunk *Grid::getChunkAt(int x, int z) {
    if (x / 10 < width && x / 10 >= 0) {
        if (z / 10 < height && z / 10 >= 0) {
            return chunkArray[x / 10][z / 10];
        }
    }
    return nullptr;
}

Chunk *Grid::getChunkAt(Vector2Int index) {
    if (index.x / 10 < width && index.x / 10 >= 0) {
        if (index.z / 10 < height && index.z / 10 >= 0) {
            return chunkArray[index.x / 10][index.z / 10];
        }
    }
    return nullptr;
}

void Grid::ClearAllWallData() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            auto tile = getTileAt(i,j);
            if (tile != nullptr)
                tile->walls.clear();
        }
    }
}

void Grid::ClearWall(Tile *tile) {
    Chunk *wallChunk = getChunkAt(tile->index);
    while (!tile->walls.empty()) {
        // Remove the wall data using the last element of the vector
        wallChunk->removeWallData(tile->walls.back());
        // Remove the last element from the vector
        tile->walls.pop_back();
    }
    tile->walls.clear();
}

void Grid::ClearWalls() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Tile *currentTile = getTileAt(i, j);
            if (currentTile != nullptr)
                ClearWall(
                        currentTile);
        }
    }
}

bool Grid::isInBounds(Vector2Int anInt) {
    return anInt.x >= 0 && anInt.x < width && anInt.z >= 0 && anInt.z < height;
}


void Grid::setTileAt(int x, int z, Tile *tile) {
    if (x < width && x >= 0) {
        if (z < height && z >= 0) {
            chunkArray[x/chunkWidth][z/chunkHeight]->getTileAt(x%chunkWidth,z%chunkHeight);
        }
    }
}

void Grid::setTileAt(Vector2Int index, Tile *tile) {
    if (index.x < width && index.x >= 0) {
        if (index.z < height && index.z >= 0) {
            chunkArray[index.x/chunkWidth][index.z/chunkHeight]->setTileAt(index.x%chunkWidth,index.z%chunkHeight,tile);
        }
    }
}

int Grid::CalculateOptimalChunkSize(int widith, int height)
{
    int start = 12;

    // Ensuring that 'start' is less than or equal to the smallest of the two numbers
    start = std::min(start, std::min(widith, height));

    for (int i=start; i>0; i--)
    {
        if (widith % i == 0 && height % i == 0)
        {
            return i;
        }
    }

    // Return 1 if there are no common divisors (excluding 1)
    return 1;
}

void Grid::removeTileAt(int x, int z) {
    if (x < width && x >= 0) {
        if (z < height && z >= 0) {
            chunkArray[x/chunkWidth][z/chunkHeight]->removeTileAt(x%chunkWidth,z%chunkHeight);
        }
    }
}

void Grid::removeTileAt(Vector2Int index) {
    if (index.x < width && index.x >= 0) {
        if (index.z < height && index.z >= 0) {
            chunkArray[index.x/chunkWidth][index.z/chunkHeight]->removeTileAt(index.x%chunkWidth,index.z%chunkHeight);
        }
    }
}




