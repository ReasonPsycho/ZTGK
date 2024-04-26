//
// Created by igork on 20.03.2024.
//

#include "Grid.h"
#include "ECS/Entity.h"
#include "ECS/Render/Components/Render.h"
#include "ECS/Render/Primitives/Primitives.h"
#include "ECS/Render/Primitives/PBRPrimitives.h"
#include "ECS/Raycasting/CollisionSystem.h"
#include "ECS/Unit/Mining/IMineable.h"
#include "ECS/Utils/Globals.h"

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

void Grid::clear() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            auto tile = gridArray[i][j];
            if ( tile == nullptr ) continue;
            tile->parentEntity->Destroy();
            gridArray[i][j] = nullptr;
        }
    }
}

void Grid::reinitWithSize(glm::ivec2 size) {
    clear();
    width = size.x; height = size.y;
    gridArray.resize(width);
    for (auto & col : gridArray) {
        col.resize(height);
    }
    auto entity = std::find_if(scene->getChildren().begin(), scene->getChildren().end(), [this](std::unique_ptr<Entity> & child){ return child->uniqueID == entityId; });
    if ( entity != scene->getChildren().end() )
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
        if (ImGui::Button("Reload walls")) {
            ClearAllWallData();
            SetUpWalls();
        }
        ImGui::Text("Width: %d", width);
        ImGui::Text("Height: %d", height);
        ImGui::Text("Tile Size: %f", tileSize);
        ImGui::Text("Offset X: %f", offsetX);
        ImGui::Text("Offset Z: %f", offsetZ);
        static glm::ivec2 newSize { width, height };
        ImGui::InputInt2("New size", glm::value_ptr(newSize));
        if (ImGui::Button("Resize"))
            reinitWithSize(newSize);
    }
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (gridArray[i][j] == nullptr) {
                ImGui::Text("No tile @ x%d y%d", i, i);
                continue;
            }

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

void Grid::GenerateTileEntities(float scale) {
    Entity *gridEntity = scene->addEntity("Grid Entity");
    entityId = gridEntity->uniqueID;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Entity *tileEntity = scene->addEntity(gridEntity, "Tile " + std::to_string(i) + " " + std::to_string(j));
            tileEntity->addComponent(std::make_unique<Tile>(i, j));
            tileEntity->transform.setLocalPosition(GridToWorldPosition(i, j));
            tileEntity->transform.setLocalScale(glm::vec3(scale, scale, scale));

            tileEntity->updateSelfAndChild();

            tileEntity->addComponent(
                    std::make_unique<BoxCollider>(tileEntity, glm::vec3(0.5, 0.5, 0.5), ztgk::game::scene->systemManager.getSystem<CollisionSystem>()));
            tileEntity->getComponent<BoxCollider>()->center =
                    tileEntity->transform.getGlobalPosition() + glm::vec3(0, 0, 0.5);
        }
    }
}

void Grid::InitializeTileEntities() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            auto tile = getTileAt(i, j);

            switch( tile->state ) {
                // todo these once relevant
                // stateData will be set by the serializer, here init components & stuff as necessary from the loaded state
                default:
                case FLOOR:
                case CHEST:
                case ORE:
                case CORE:
                case UNIT:
                case state_count:   // keep this one empty or signal error, this is unreachable
                    break;
                case WALL:

                    break;
            }
        }
    }
}

void Grid::LoadTileEntities(float scale, CollisionSystem *collisionSystem) {
    Entity *gridEntity = scene->addEntity("Grid Entity");
    entityId = gridEntity->uniqueID;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Entity *tileEntity = scene->addEntity(gridEntity, "Tile " + std::to_string(i) + " " + std::to_string(j));
            tileEntity->addComponent(std::make_unique<Tile>(i, j));
            tileEntity->transform.setLocalPosition(GridToWorldPosition(i, j));
            tileEntity->transform.setLocalScale(glm::vec3(scale, scale, scale));

            if (i >= width / 4 && i < (width - width / 4) && j >= height / 4 && j < (height - height / 4)) {
                tileEntity->getComponent<Tile>()->state = FLOOR;

            } else {
                tileEntity->getComponent<Tile>()->state = WALL;
                tileEntity->getComponent<Tile>()->vacant = false;
                tileEntity->addComponent(std::make_unique<IMineable>(1.0f, Vector2Int(i, j), this));

            }

            tileEntity->updateSelfAndChild();

            tileEntity->addComponent(
                    std::make_unique<BoxCollider>(tileEntity, glm::vec3(0.5, 0.5, 0.5), collisionSystem));
            tileEntity->getComponent<BoxCollider>()->center =
                    tileEntity->transform.getGlobalPosition() + glm::vec3(0, 0, 0.5);
        }
    }

    SetUpWalls();
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

    float translateLength = tileSize / 2.0f;
    bool isDiagonal = ((tile->index.x + tile->index.z) % 2 == 0);
    if (tile->state != WALL) {
        tile->walls.clear();
        glm::mat4x4 floorMatrix = tile->getEntity()->transform.getModelMatrix();
        floorMatrix = glm::translate(floorMatrix, glm::vec3(0, -translateLength, 0));
        floorMatrix = glm::rotate(floorMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
        tile->walls.push_back(WallData(floorMatrix, (isDiagonal ? 0 : 1), 0, 0, 0));
    } else {


        Tile *northNeighbour = getTileAt(tile->index.x + 1, tile->index.z);
        if (northNeighbour == nullptr || northNeighbour->state != WALL) {
            glm::mat4x4 northMatrix = tile->getEntity()->transform.getModelMatrix();
            northMatrix = glm::translate(northMatrix, glm::vec3(translateLength, 0, 0));
            northMatrix = glm::rotate(northMatrix, glm::radians(-90.0f), glm::vec3(0, 1, 0));
            tile->walls.push_back(WallData(northMatrix, 2, 0, 0, 0));
        }

        Tile *southNeighbour = getTileAt(tile->index.x - 1, tile->index.z);
        if (southNeighbour == nullptr || southNeighbour->state != WALL) {
            glm::mat4x4 southMatrix = tile->getEntity()->transform.getModelMatrix();
            southMatrix = glm::translate(southMatrix, glm::vec3(-translateLength, 0, 0));
            southMatrix = glm::rotate(southMatrix, glm::radians(90.0f), glm::vec3(0, 1, 0));
            tile->walls.push_back(WallData(southMatrix, 2, 0, 0, 0));
        }
        Tile *eastNeighbour = getTileAt(tile->index.x, tile->index.z + 1);
        if (eastNeighbour == nullptr || eastNeighbour->state != WALL) {
            glm::mat4x4 eastMatrix = tile->getEntity()->transform.getModelMatrix();
            eastMatrix = glm::translate(eastMatrix, glm::vec3(0, 0, translateLength));
            eastMatrix = glm::rotate(eastMatrix, glm::radians(90.0f), glm::vec3(0, 0, 1));
            tile->walls.push_back(WallData(eastMatrix, 2, 0, 0, 0));
        }

        Tile *westNeighbour = getTileAt(tile->index.x, tile->index.z - 1);
        if (westNeighbour == nullptr || westNeighbour->state != WALL) {
            glm::mat4x4 westMatrix = tile->getEntity()->transform.getModelMatrix();
            westMatrix = glm::translate(westMatrix, glm::vec3(0, 0, -translateLength));
            //  westMatrix = glm::rotate(westMatrix,glm::radians(-90.0f),glm::vec3 (1,0,0));
            tile->walls.push_back(WallData(westMatrix, 2, 0, 0, 0));
        }

        glm::mat4x4 topMatrix = tile->getEntity()->transform.getModelMatrix();
        topMatrix = glm::translate(topMatrix, glm::vec3(0, translateLength, 0));
        topMatrix = glm::rotate(topMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
        tile->walls.push_back(WallData(topMatrix, 2, 0, 0, 0));
    }
}

void Grid::DestroyWallsOnTile(Vector2Int tileIndex) {
    Tile* currentTile = getTileAt(tileIndex);
    currentTile->state = FLOOR;
    currentTile->vacant = true;
}

void Grid::ClearAllWallData() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            auto tile = gridArray[i][j];
            if ( tile != nullptr )
                tile->walls.clear();
        }
    }
}


