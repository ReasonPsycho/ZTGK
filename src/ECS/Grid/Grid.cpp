//
// Created by igork on 20.03.2024.
//

#include "Grid.h"
#include "ECS/Entity.h"
#include "ECS/Render/Components/Render.h"
#include "ECS/Render/Primitives/Primitives.h"
#include "ECS/Render/Primitives/PBRPrimitives.h"


/**
 * @brief Constructs a new Grid object.
 *
 * The Grid constructor initializes a new Grid object with the specified width, height, and tile size.
 * It also initializes the entity member variable by calling the getEntity() function.
 * The gridArray member variable, a 2D vector, is resized according to the specified width and height.
 * Each element of the gridArray is then initialized with a new Tile object.
 *
 * @param width The width of the grid.
 * @param height The height of the grid.
 * @param tileSize The size of each tile in the grid.
 */
Grid::Grid(int width, int height, float tileSize, Entity* parentEntity) {

    setEntity(parentEntity); // set the parent entity (the entity that the grid is attached to
    this->entity = getEntity();

    this->width = width;
    this->height = height;
    this->tileSize = tileSize;

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

/**
 * @brief Converts a grid index to a world position.
 *
 * The GridToWorldPosition function converts a grid index to a world position.
 * It multiplies the x and z indices by the tileSize and adds the result to the entity's global position.
 *
 * @param index The index of the tile.
 * @return Vector3 The world position of the tile.
 */
Vector3 Grid::GridToWorldPosition(Vector2Int index) const {
    return {index.x * tileSize + entity->transform.getGlobalPosition().x,
            0 + entity->transform.getGlobalPosition().y,
            index.z * tileSize + entity->transform.getGlobalPosition().z};
}

/**
 * @brief Converts a grid index to a world position.
 *
 * The GridToWorldPosition function converts a grid index to a world position.
 * It multiplies the x and z indices by the tileSize and adds the result to the entity's global position.
 *
 * @param x The x-index of the tile.
 * @param z The z-index of the tile.
 * @return Vector3 The world position of the tile.
 */
Vector3 Grid::GridToWorldPosition(int x, int z) const {
    return GridToWorldPosition(Vector2Int(x, z));
}

/**
 * @brief Converts a world position to a grid index.
 *
 * The WorldToGridPosition function converts a world position to a grid index.
 * It subtracts the entity's global position from the position, then divides the result by the tileSize.
 *
 * @param position The world position of the tile.
 * @return Vector2Int The index of the tile.
 */
Vector2Int Grid::WorldToGridPosition(Vector3 position) const {
    return {static_cast<int>((int) (position.x - entity->transform.getGlobalPosition().x) / tileSize),
            static_cast<int>((int) (position.z - entity->transform.getGlobalPosition().z) / tileSize)};
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
    ImGui::PopID();

}

/**
 * @brief Renders the tiles in the grid.
 *
 * The RenderTiles function renders the tiles in the grid by creating an entity for each tile.
 * The entity is named "Tile" followed by the x and z indices of the tile.
 * The entity is then added to the scene and its position is set based on the tile index and size.
 *
 * @param scene The scene in which to render the tiles.
 * @param scale The scale of the tiles.
 */
void Grid::RenderTiles(Scene *scene, float scale, Model* tileModel){
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            std::string name = "Tile" + std::to_string(gridArray[i][j]->index.x) + '-' + std::to_string(gridArray[i][j]->index.z);
            Entity* tileEntity = scene->addEntity(parentEntity, name);
            // todo zamienic na primitive
            tileEntity->addComponent(make_unique<Render>(tileModel));
            tileEntity->transform.setLocalScale(VectorUtils::Vector3ToGlmVec3(Vector3(scale, scale, scale)));

            glm::vec3 position = VectorUtils::Vector3ToGlmVec3(Vector3(parentEntity->transform.getGlobalPosition().x + gridArray[i][j]->index.x * tileSize + offsetX,
                                                                                 parentEntity->transform.getGlobalPosition().y,
                                                                              parentEntity->transform.getGlobalPosition().z + gridArray[i][j]->index.z * tileSize + offsetZ));
            tileEntity->transform.setLocalPosition(position);
            tileEntity->transform.setLocalRotation(glm::quat(glm::vec3(glm::half_pi<float>(), 0, 0)));


        }
    }

}

