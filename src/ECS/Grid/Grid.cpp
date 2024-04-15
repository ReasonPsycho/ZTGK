//
// Created by igork on 20.03.2024.
//

#include "Grid.h"
#include "ECS/Entity.h"
#include "ECS/Render/Components/Render.h"
#include "ECS/Render/Primitives/Primitives.h"
#include "ECS/Render/Primitives/PBRPrimitives.h"



Grid::Grid(Scene* scene,int width, int height, float tileSize, Vector3 Position) {
    this->name = "Grid";
    this->scene = scene;
    this->width = width;
    this->height = height;
    this->tileSize = tileSize;
    this->Position = Position;
    // center the grid
    offsetX = -width*tileSize/2.0f;
    offsetZ = -height*tileSize/2.0f;

    gridArray.resize(width);
    for (int i = 0; i < width; i++) {
        gridArray[i].resize(height);
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            gridArray[i][j] = new Tile(i, j);
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
    return gridArray[x][z];
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
    return glm::vec3(Position.x + index.x * tileSize + offsetX, Position.y, Position.z + index.z * tileSize + offsetZ);
}


const glm::vec3 Grid::GridToWorldPosition(int x, int z) const {
    return GridToWorldPosition(Vector2Int(x, z));
}

Vector2Int Grid::WorldToGridPosition(Vector3 position) const {
    return Vector2Int((int) ((position.x - Position.x - offsetX) / tileSize), (int) ((position.z - Position.z - offsetZ) / tileSize));
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
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            ImGui::PushID(gridArray[i][j]->uniqueID);
            if(ImGui::CollapsingHeader(("Tile " + std::to_string(i) + std::to_string(j)).c_str())) {
                gridArray[i][j]->showImGuiDetails(camera);

            }
            ImGui::PopID();
        }
    }

    ImGui::PopID();

}

void Grid::RenderTiles(float scale, Model* tileModel){
    Entity* tileEntity;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            tileEntity = new Entity(scene ,"Tile" + std::to_string(i) + std::to_string(j));
            tileEntity->addComponent(std::make_unique<Render>(new Model(*tileModel)));
            tileEntity->addComponent(std::make_unique<Tile>(i, j));
            tileEntity->transform.setLocalPosition(GridToWorldPosition(i, j));
            tileEntity->transform.setLocalScale(glm::vec3(scale, scale,scale));
            scene->addEntity(tileEntity, tileEntity->name);
        }
    }

}

void Grid::addComponent(void *component) {
    auto c = static_cast<Component*>(component);
    tiles[c->uniqueID].push_back(dynamic_cast<Tile*>(c));

}

void Grid::removeComponent(void *component) {
    auto c = static_cast<Component*>(component);
    erase(tiles[c->uniqueID], dynamic_cast<Tile*>(c));

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



