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
#include "ECS/Gameplay/Pranium.h"
#include "ECS/Gameplay/WashingMachineTile.h"
#include "ECS/Gameplay/WashingMachine.h"
#include "ECS/Unit/Unit.h"
#include "ECS/Unit/UnitAI/UnitAI.h"
#include "ECS/Unit/UnitAI/StateMachine/States/IdleState.h"
#include "ECS/Render/Components/AnimationPlayer.h"
#include "ECS/Render/ModelLoading/ModelLoadingManager.h"
#include "ECS/Unit/Equipment/ConcreteItems/ItemTypes.h"

#include <iostream>
#include <cstdlib> // Required for rand()
#include <ctime>   // Required for time()
#include <future>

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

    int chunkSize = CalculateOptimalChunkSize(width, height);
    chunkHeight = chunkSize;
    chunkWidth = chunkHeight;

    for (int i = 0; i < width / chunkWidth; i++) {
        std::vector<Chunk *> chunkLine;    // Create a new line
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
    int chunkSize = CalculateOptimalChunkSize(size.x, size.x);
    chunkHeight = chunkSize;
    chunkWidth = chunkHeight;

    for (int i = 0; i < width / chunkWidth; i++) {
        std::vector<Chunk *> chunkLine;    // Create a new line
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
            return chunkArray[x / chunkWidth][z / chunkHeight]->getTileAt(x % chunkWidth, z % chunkHeight);
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
            return chunkArray[index.x / chunkWidth][index.z / chunkHeight]->getTileAt(index.x % chunkWidth, index.z % chunkHeight);
        }
    }
    return nullptr;
}


const glm::vec3 Grid::GridToWorldPosition(Vector2Int index) const {

    float worldPosX = Position.x + index.x * tileSize + tileSize / 2;
    float worldPosY = Position.y;
    float worldPosZ = Position.z + index.z * tileSize + tileSize / 2;
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
    for (int i = 0; i < width / chunkWidth; i++) {
        for (int j = 0; j < height / chunkHeight; j++) {
            Entity *chunkEntity = scene->addEntity(gridEntity, "Chunk " + std::to_string(i) + " " + std::to_string(j));
            chunkEntity->addComponent(make_unique<Chunk>(Vector2Int(i, j), this, chunkWidth, chunkHeight));
            chunkArray[i][j] = chunkEntity->getComponent<Chunk>();
            chunkEntity->transform.setLocalPosition(glm::vec3(i * chunkWidth * tileSize, 0, j * chunkHeight * tileSize));
            chunkEntity->forceUpdateSelfAndChild();
            chunkEntity->addComponent(std::make_unique<BoxCollider>(chunkEntity, glm::vec3(chunkWidth * tileSize, 0.8, chunkHeight * tileSize), CollisionType::CHUNK));
            chunkEntity->getComponent<BoxCollider>()->setCenter(chunkEntity->transform.getGlobalPosition() + glm::vec3(chunkWidth, 0, chunkHeight) - glm::vec3(0, 0, 0));
            chunkEntity->getComponent<BoxCollider>()->size = glm::vec3(10, 1, 10);
            chunkEntity->getComponent<BoxCollider>()->coordsToExcludeFromUpdate = "xyz";

            for (int x = 0; x < chunkWidth; ++x) {
                for (int z = 0; z < chunkHeight; ++z) {
                    Entity *tileEntity = scene->addEntity(chunkEntity, "Tile " + std::to_string(x) + " " + std::to_string(z));
                    tileEntity->addComponent(std::make_unique<Tile>(i * chunkWidth + x, j * chunkHeight + z, chunkEntity->getComponent<Chunk>()));
                    tileEntity->transform.setLocalPosition(glm::vec3(x * tileSize + tileSize / 2, 0, z * tileSize + tileSize / 2)); //TODO find where it is
                    tileEntity->transform.setLocalScale(glm::vec3(scale, scale, scale));


                    tileEntity->forceUpdateSelfAndChild();
                    tileEntity->addComponent(
                            std::make_unique<BoxCollider>(tileEntity, glm::vec4(1, 1, 1, 1), CollisionType::TILE));

                }
            }
            Entity* localLight = scene->addEntity(chunkEntity,"LocalLight");
            localLight->addComponent(make_unique<PointLight>(PointLightData(glm::vec4(glm::vec3(1), 1), glm::vec4(glm::vec3(0.1), 1), glm::vec4(1, 1, 1, 1), 0.1f, 0.2f,0.05f)));
            localLight->transform.setLocalPosition(glm::vec3(0, 7,0));
            chunkArray[i][j]->localLight = localLight->getComponent<PointLight>();
            localLight->forceUpdateSelfAndChild();
            localLight->getComponent<PointLight>()->setIsDirty(true);
        }
    }
    gridEntity->forceUpdateSelfAndChild();
}

void Grid::InitializeTileEntities() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            auto tile = getTileAt(i, j);

            auto tileEntity = tile->getEntity();
            tileEntity->getComponent<BoxCollider>()->setCenter(
                    tileEntity->transform.getGlobalPosition() + glm::vec3(0, tileEntity->getComponent<Tile>()->state == FLOOR ? -2 : 0, 0));
            tileEntity->getComponent<BoxCollider>()->coordsToExcludeFromUpdate = "xz";
            if(tileEntity->getComponent<BoxCollider>()->getCenter().y == -2){
                tileEntity->getComponent<BoxCollider>()->boxColliderData.color = glm::vec4(0, 1, 0, 1);
            }

            tile->isInFogOfWar = true;
            switch (tile->state) {
                // todo these once relevant
                // stateData will be set by the serializer, here init components & stuff as necessary from the loaded state
                default:
                case FLOOR:
                    break;
                case ORE:
                    tile->getEntity()->addComponent(std::make_unique<Pranium>(5.0f, Vector2Int(i, j), this));
                    tile->getEntity()->getComponent<Pranium>()->generatePranium(ztgk::game::washingMachineModel);
                    tile->getEntity()->getComponent<BoxCollider>()->coordsToExcludeFromUpdate = "xyz";
                    tile->getEntity()->getComponent<BoxCollider>()->size = glm::vec3(1, 1, 1);
                    tile->getEntity()->getComponent<BoxCollider>()->setCenter(tile->getEntity()->transform.getGlobalPosition() + glm::vec3(0, 0, 0));
                    ++ztgk::game::pranium_needed_to_win;
                    break;
                case CORE:
                    tile->isInFogOfWar = false;
                    centerTile = tile;
                    tile->getEntity()->addComponent(std::make_unique<WashingMachineTile>(ztgk::game::scene->systemManager.getSystem<WashingMachine>(), Vector2Int(i, j), this));
                    tile->getEntity()->getComponent<BoxCollider>()->size = glm::vec3(1, 5, 1);
                    break;
                case SPONGE:
                    SpawnUnit(tile->index, true);
                    break;
                case state_count:   // keep this one empty or signal error, this is unreachable
                    break;
                case CHEST:
                    // todo item type id
                    tile->getEntity()->addComponent(std::make_unique<MineableChest>(Vector2Int(i, j), this, 2));

                    tile->getEntity()->getComponent<BoxCollider>()->coordsToExcludeFromUpdate = "xyz";
                    tile->getEntity()->getComponent<BoxCollider>()->size = glm::vec3(1, 1, 1);
                    tile->getEntity()->getComponent<BoxCollider>()->setCenter(tile->getEntity()->transform.getGlobalPosition() + glm::vec3(0, 0, 0));
                    tile->getEntity()->addComponent(std::make_unique<Render>(ztgk::game::chestModel));
                    break;
                case WALL:
                    tile->getEntity()->addComponent(std::make_unique<IMineable>(1.0f, Vector2Int(i, j), this));
                    break;
                case SHROOM:
                    //todo add shroom spawning with model etc
                case BUG:
                    SpawnUnit(tile->index, false);
                    break;
            }
        }
    }
}

void Grid::LoadTileEntities(float scale) {
    gridEntity = scene->addEntity("Grid Entity");
    entityId = gridEntity->uniqueID;
    gridEntity->updateChildren = false;
    for (int i = 0; i < width / chunkWidth; i++) {
        for (int j = 0; j < height / chunkHeight; j++) {
            Entity *chunkEntity = scene->addEntity(gridEntity, "Chunk " + std::to_string(i) + " " + std::to_string(j));
            chunkEntity->addComponent(make_unique<Chunk>(Vector2Int(i, j), this, chunkWidth, chunkHeight));
            chunkArray[i][j] = chunkEntity->getComponent<Chunk>();
            chunkEntity->transform.setLocalPosition(glm::vec3(i * chunkWidth * tileSize, 0, j * chunkHeight * tileSize));
            chunkEntity->forceUpdateSelfAndChild();
            chunkEntity->addComponent(std::make_unique<BoxCollider>(chunkEntity, glm::vec3(chunkWidth * tileSize, 0.8, chunkHeight * tileSize), CollisionType::CHUNK));
            chunkEntity->getComponent<BoxCollider>()->setCenter(chunkEntity->transform.getGlobalPosition() + glm::vec3(chunkWidth, 0, chunkHeight) - glm::vec3(0, 0, 0));
            chunkEntity->getComponent<BoxCollider>()->size = glm::vec3(10, 1, 10);
            chunkEntity->getComponent<BoxCollider>()->coordsToExcludeFromUpdate = "xyz";

            for (int x = 0; x < chunkWidth; ++x) {
                for (int z = 0; z < chunkHeight; ++z) {
                    Entity *tileEntity = scene->addEntity(chunkEntity, "Tile " + std::to_string(x) + " " + std::to_string(z));
                    tileEntity->addComponent(std::make_unique<Tile>(i * chunkWidth + x, j * chunkHeight + z, chunkEntity->getComponent<Chunk>()));
                    tileEntity->transform.setLocalPosition(glm::vec3(x * tileSize + tileSize / 2, 0, z * tileSize + tileSize / 2)); //TODO find where it is 
                    tileEntity->transform.setLocalScale(glm::vec3(scale, scale, scale));

                    if ((i >= chunkWidth / 4 && i < (chunkWidth - chunkWidth / 4) && j >= chunkHeight / 4 && j < (chunkHeight - chunkHeight / 4)) && (x * i != 40 || z * j != 40)) {
                        tileEntity->getComponent<Tile>()->state = FLOOR;

                    } else {
                        tileEntity->getComponent<Tile>()->state = WALL;
                        tileEntity->addComponent(std::make_unique<IMineable>(1.0f, tileEntity->getComponent<Tile>()->index, this));

                    }
                    if (i * x > 40 && i * x < 44 && j * z > 40 && j * z < 44) {
                        tileEntity->getComponent<Tile>()->state = ORE;
                        tileEntity->addComponent(std::make_unique<Pranium>(5.0f, tileEntity->getComponent<Tile>()->index, this));
                        tileEntity->getComponent<Pranium>()->generatePranium(ztgk::game::washingMachineModel);
                    }

                    tileEntity->forceUpdateSelfAndChild();
                    tileEntity->addComponent(
                            std::make_unique<BoxCollider>(tileEntity, glm::vec4(1, 1, 1, 1), CollisionType::TILE));
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
    setTileAt(tile->index, tile);
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
        tile->dirtinessLevel = std::rand() % 101;
        glm::mat4x4 floorMatrix = tile->getEntity()->transform.getModelMatrix();
        floorMatrix = glm::translate(floorMatrix, glm::vec3(0, -translateLength, 0));
        floorMatrix = glm::rotate(floorMatrix, glm::radians(-90.0f), glm::vec3(1, 0, 0));
        tile->walls.push_back(
                wallChunk->addWallData(make_unique<WallData>(floorMatrix, tile->dirtinessLevel, tile->isInFogOfWar, 0, 0, (isDiagonal ? 1 : 2), (isDiagonal ? 1 : 2), 0, (isDiagonal ? 1 : 2))));
    } else if (tile->state == WALL) {
        Tile *northNeighbour = getTileAt(tile->index.x + 1, tile->index.z);
        if (northNeighbour == nullptr || northNeighbour->state != WALL) {
            glm::mat4x4 northMatrix = tile->getEntity()->transform.getModelMatrix();
            northMatrix = glm::translate(northMatrix, glm::vec3(translateLength, 0, 0));
            northMatrix = glm::rotate(northMatrix, glm::radians(90.0f), glm::vec3(0, 1, 0));
            tile->walls.push_back(wallChunk->addWallData(make_unique<WallData>(northMatrix, tile->dirtinessLevel, tile->isInFogOfWar, 0, 0, 0, 0, 0, 0)));
            isSurrounded = false;
        }

        Tile *southNeighbour = getTileAt(tile->index.x - 1, tile->index.z);
        if (southNeighbour == nullptr || southNeighbour->state != WALL) {
            glm::mat4x4 southMatrix = tile->getEntity()->transform.getModelMatrix();
            southMatrix = glm::translate(southMatrix, glm::vec3(-translateLength, 0, 0));
            southMatrix = glm::rotate(southMatrix, glm::radians(-90.0f), glm::vec3(0, 1, 0));
            tile->walls.push_back(wallChunk->addWallData(make_unique<WallData>(southMatrix, tile->dirtinessLevel, tile->isInFogOfWar, 0, 0, 0, 0, 0, 0)));
            isSurrounded = false;
        }

        Tile *eastNeighbour = getTileAt(tile->index.x, tile->index.z + 1);
        if (eastNeighbour == nullptr || eastNeighbour->state != WALL) {
            glm::mat4x4 eastMatrix = tile->getEntity()->transform.getModelMatrix();
            eastMatrix = glm::translate(eastMatrix, glm::vec3(0, 0, translateLength));
            eastMatrix = glm::rotate(eastMatrix, glm::radians(-90.0f), glm::vec3(0, 0, 1));
            tile->walls.push_back(wallChunk->addWallData(make_unique<WallData>(eastMatrix, tile->dirtinessLevel, tile->isInFogOfWar, 0, 0, 0, 0, 0, 0)));
            isSurrounded = false;
        }

        Tile *westNeighbour = getTileAt(tile->index.x, tile->index.z - 1);
        if (westNeighbour == nullptr || westNeighbour->state != WALL) {
            glm::mat4x4 westMatrix = tile->getEntity()->transform.getModelMatrix();
            westMatrix = glm::translate(westMatrix, glm::vec3(0, 0, -translateLength));
            westMatrix = glm::rotate(westMatrix, glm::radians(180.0f), glm::vec3(1, 0, 0));
            tile->walls.push_back(wallChunk->addWallData(make_unique<WallData>(westMatrix, tile->dirtinessLevel, tile->isInFogOfWar, 0, 0, 0, 0, 0, 0)));
            isSurrounded = false;
        }

        glm::mat4x4 topMatrix = tile->getEntity()->transform.getModelMatrix();
        topMatrix = glm::translate(topMatrix, glm::vec3(0, translateLength, 0));
        topMatrix = glm::rotate(topMatrix, glm::radians(-90.0f), glm::vec3(1, 0, 0));
        tile->walls.push_back(
                wallChunk->addWallData(make_unique<WallData>(topMatrix, tile->dirtinessLevel, tile->isInFogOfWar, 0, 0, 0, 0, 0, 0)));
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
    UpdateFogData(currentTile);
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
            auto tile = getTileAt(i, j);
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
            chunkArray[x / chunkWidth][z / chunkHeight]->getTileAt(x % chunkWidth, z % chunkHeight);
        }
    }
}

void Grid::setTileAt(Vector2Int index, Tile *tile) {
    if (index.x < width && index.x >= 0) {
        if (index.z < height && index.z >= 0) {
            chunkArray[index.x / chunkWidth][index.z / chunkHeight]->setTileAt(index.x % chunkWidth, index.z % chunkHeight, tile);
        }
    }
}

int Grid::CalculateOptimalChunkSize(int widith, int height) {
    int start = 12;

    // Ensuring that 'start' is less than or equal to the smallest of the two numbers
    start = std::min(start, std::min(widith, height));

    for (int i = start; i > 0; i--) {
        if (widith % i == 0 && height % i == 0) {
            return i;
        }
    }

    // Return 1 if there are no common divisors (excluding 1)
    return 1;
}

void Grid::removeTileAt(int x, int z) {
    if (x < width && x >= 0) {
        if (z < height && z >= 0) {
            chunkArray[x / chunkWidth][z / chunkHeight]->removeTileAt(x % chunkWidth, z % chunkHeight);
        }
    }
}

void Grid::removeTileAt(Vector2Int index) {
    if (index.x < width && index.x >= 0) {
        if (index.z < height && index.z >= 0) {
            chunkArray[index.x / chunkWidth][index.z / chunkHeight]->removeTileAt(index.x % chunkWidth, index.z % chunkHeight);
        }
    }
}

void Grid::SetUpChunks() {
    for (int i = 0; i < width / tileSize; i++) {
        for (int j = 0; j < height / tileSize; j++) {
            Chunk *currentChunk = getChunkAt(i, j);
            if (currentChunk != nullptr)
                currentChunk->CalculateChunkData();
        }
    }
}
std::vector<Tile *> Grid::GetNeighbours(Vector2Int gridpos, bool includeDiagonals) {
    std::vector<Tile *> neighbours;
    if (isInBounds(Vector2Int(gridpos.x + 1, gridpos.z))) {
        neighbours.push_back(getTileAt(gridpos.x + 1, gridpos.z));
    }
    if (isInBounds(Vector2Int(gridpos.x - 1, gridpos.z))) {
        neighbours.push_back(getTileAt(gridpos.x - 1, gridpos.z));
    }
    if (isInBounds(Vector2Int(gridpos.x, gridpos.z + 1))) {
        neighbours.push_back(getTileAt(gridpos.x, gridpos.z + 1));
    }
    if (isInBounds(Vector2Int(gridpos.x, gridpos.z - 1))) {
        neighbours.push_back(getTileAt(gridpos.x, gridpos.z - 1));
    }
    if(includeDiagonals) {
        if (isInBounds(Vector2Int(gridpos.x + 1, gridpos.z + 1))) {
            neighbours.push_back(getTileAt(gridpos.x + 1, gridpos.z + 1));
        }
        if (isInBounds(Vector2Int(gridpos.x - 1, gridpos.z - 1))) {
            neighbours.push_back(getTileAt(gridpos.x - 1, gridpos.z - 1));
        }
        if (isInBounds(Vector2Int(gridpos.x + 1, gridpos.z - 1))) {
            neighbours.push_back(getTileAt(gridpos.x + 1, gridpos.z - 1));
        }
        if (isInBounds(Vector2Int(gridpos.x - 1, gridpos.z + 1))) {
            neighbours.push_back(getTileAt(gridpos.x - 1, gridpos.z + 1));
        }
    }
    return neighbours;
}

void Grid::UpdateFogData(Tile *tile) {
    const Vector2Int neighboursIndexes[4] = {
            Vector2Int(0, 1),
            Vector2Int(0, -1),
            Vector2Int(-1, 0),
            Vector2Int(1, 0)
    };

    std::vector<Vector2Int> open;
    std::unordered_set<Vector2Int, Vector2IntHasher> closedSet;
    std::unordered_set<Vector2Int, Vector2IntHasher> edgeSet;

    open.reserve(100);
    closedSet.reserve(100);
    edgeSet.reserve(100);

    open.push_back(tile->index);
    closedSet.insert(tile->index);

    while (!open.empty()) {
        Vector2Int current = open.back();
        open.pop_back();

        for (const auto& offset : neighboursIndexes) {
            Vector2Int neighbourIndex = current + offset;
            if (closedSet.find(neighbourIndex) != closedSet.end()) continue;

            Tile *neighbourTile = getTileAt(neighbourIndex.x, neighbourIndex.z);
            if (neighbourTile != nullptr) {
                if (neighbourTile->state == FLOOR || neighbourTile->state == CORE || neighbourTile->state == CHEST || neighbourTile->state == SPONGE) {
                    open.push_back(neighbourIndex);
                } else {
                    edgeSet.insert(neighbourIndex);
                }
                closedSet.insert(neighbourIndex);
            }
        }
    }

    // Function to expand edges in parallel
    auto expandEdges = [neighboursIndexes, this](const std::unordered_set<Vector2Int, Vector2IntHasher>& edgeSet, std::unordered_set<Vector2Int, Vector2IntHasher>& closedSet) {
        std::unordered_set<Vector2Int, Vector2IntHasher> newEdgeSet;

        for (const auto& current : edgeSet) {
            for (const auto& offset : neighboursIndexes) {
                Vector2Int neighbourIndex = current + offset;
                if (closedSet.find(neighbourIndex) != closedSet.end()) continue;

                Tile *neighbourTile = getTileAt(neighbourIndex.x, neighbourIndex.z);
                if (neighbourTile != nullptr) {
                    newEdgeSet.insert(neighbourIndex);
                    closedSet.insert(neighbourIndex);
                }
            }
        }

        return newEdgeSet;
    };

    std::vector<std::future<std::unordered_set<Vector2Int, Vector2IntHasher>>> futures;

    // Expand edges with parallel tasks
    for (int i = 0; i < visibilityRange; ++i) {
        futures.push_back(std::async(std::launch::async, expandEdges, edgeSet, std::ref(closedSet)));
        edgeSet.clear();
        for (auto& future : futures) {
            std::unordered_set<Vector2Int, Vector2IntHasher> newEdges = future.get();
            edgeSet.insert(newEdges.begin(), newEdges.end());
        }
        futures.clear();
    }

    // Update fog of war
    for (const auto& index : closedSet) {
        Tile *tile = getTileAt(index.x, index.z);
        if (tile != nullptr) {
            tile->isInFogOfWar = false;
            tile->changeWallsFogOfWarState(false);
        }
    }
}




Entity * Grid::SpawnUnit(Vector2Int gridPos, bool isAlly){
    auto modelLoadingManager = ModelLoadingManager();
    modelLoadingManager.Innit();
    auto gabka = ztgk::game::playerModel;

    string modelPathGabkaMove = "res/models/gabka/pan_gabka_move.fbx";
    string modelPathGabkaIdle = "res/models/gabka/pan_gabka_idle.fbx";
    string modelPathGabkaMine = "res/models/gabka/pan_gabka_mine.fbx";
    string modelPathGabkaAttack = "res/models/gabka/pan_gabka_attack.fbx";


    Entity* UnitEntity = ztgk::game::scene->addEntity(isAlly ? "Sponge" : "Enemy");
    UnitEntity->addComponent(make_unique<Render>(isAlly ? ztgk::game::playerModel : ztgk::game::bugModel));
    UnitEntity->transform.setLocalScale(glm::vec3(1, 1, 1));
    UnitEntity->transform.setLocalPosition(glm::vec3(0, -1, 0));
    UnitEntity->transform.setLocalRotation(glm::vec3(0, 0, 0));
    UnitEntity->updateSelfAndChild();
    UnitEntity->addComponent(make_unique<BoxCollider>(UnitEntity, glm::vec3(1, 1, 1)));
    UnitEntity->getComponent<BoxCollider>()->setCenter(UnitEntity->transform.getGlobalPosition() + glm::vec3(0, 0, 0.5));
    UnitEntity->addComponent(make_unique<Unit>(isAlly? "Sponge" : "Enemy", this, gridPos, isAlly ? Unit::ALLY_BASE : Unit::ENEMY_BASE, isAlly));

    auto stateManager = new StateManager(UnitEntity->getComponent<Unit>());
    stateManager->currentState = new IdleState(this);
    stateManager->currentState->unit = UnitEntity->getComponent<Unit>();
    UnitEntity->addComponent(make_unique<UnitAI>(UnitEntity->getComponent<Unit>(), stateManager));
    if(isAlly) {
        UnitEntity->addComponent(make_unique<AnimationPlayer>());
        UnitEntity->getComponent<AnimationPlayer>()->animationMap[modelPathGabkaMove] = modelLoadingManager.GetAnimation(
                modelPathGabkaMove, gabka);
        UnitEntity->getComponent<AnimationPlayer>()->animationMap[modelPathGabkaIdle] = modelLoadingManager.GetAnimation(
                modelPathGabkaIdle, gabka);
        UnitEntity->getComponent<AnimationPlayer>()->animationMap[modelPathGabkaMine] = modelLoadingManager.GetAnimation(
                modelPathGabkaMine, gabka);
        UnitEntity->getComponent<AnimationPlayer>()->animationMap[modelPathGabkaAttack] = modelLoadingManager.GetAnimation(
                modelPathGabkaAttack, gabka);
    }
    return UnitEntity;
}