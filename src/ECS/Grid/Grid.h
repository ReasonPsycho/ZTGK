//
// Created by igork on 20.03.2024.
//

#ifndef ZTGK_GRID_H
#define ZTGK_GRID_H


#include <vector>
#include "Tile.h"
#include "ECS/Component.h"
#include "ECS/Utils/VectorUtils.h"
#include "ECS/Scene.h"
#include "ECS/Render/ModelLoading/Model.h"

class CollisionSystem;
class Grid : public System{
public:
    //number of tiles in the grid
    int width;
    int height;

    //size of the tiles
    float tileSize;

    //2D array of tiles
    std::vector<std::vector<Tile*>> gridArray;

    Scene* scene;
    Vector3 Position;

    // Constructors
    Grid() = default;
    Grid(Scene* scene ,int width, int height, float tileSize, Vector3 Position = Vector3(0,0,0));
    Grid(Grid* grid);

    // Destructor
    ~Grid();

    //Other methods

    //get the tile at a specific index
    Tile* getTileAt(int x, int z);
    Tile* getTileAt(Vector2Int index);

    //get the tile at a specific world position
    [[nodiscard]] const glm::vec3 GridToWorldPosition(Vector2Int index) const;
    [[nodiscard]] const glm::vec3 GridToWorldPosition(int x, int z) const;

    //get the index of a tile in specific world position
    [[nodiscard]] Vector2Int WorldToGridPosition(Vector3 position) const;

    //loads and distributes the tile entities in world space
    void LoadTileEntities(float scale, CollisionSystem *collisionSystem);

    void SetUpWalls();
    void SetUpWall(Tile* tile);
    //system methods
    void addComponent(void *component) override;
    void removeComponent(void *component) override;
    const std::type_index *getComponentTypes() override;
    int getNumComponentTypes() override;
    void showImGuiDetails(Camera *camera) override;

private:
    float offsetX = 0;
    float offsetZ = 0;

    std::array<std::type_index, 1> componentTypes = {
        std::type_index(typeid(Tile))
    };
};


#endif //ZTGK_GRID_H
