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
#include "Chunk.h"

class CollisionSystem;

class Grid : public System {
public:
    //number of tiles in the grid
    int width;
    int height;

    int chunkWidth = 10;
    int chunkHeight = 10;

    //size of the tiles
    float tileSize;

    //2D array of tiles
    std::vector<std::vector<Chunk*>> chunkArray;
    Entity *gridEntity;
    Tile* centerTile;
    Scene *scene;
    Vector3 Position;
    unsigned entityId = (unsigned) -1;

    // Constructors
    Grid() = default;

    Grid(Scene *scene, int width, int height, float tileSize, Vector3 Position = Vector3(0, 0, 0));

    // Destructor
    ~Grid();

    // save loading
    // clears all entities, changes size, regenerates entities for size
    void reinitWithSize(glm::ivec2 size);

    // removes all related entities, used by reinit
    void Clear();

    // generates empty tile entities, used by reinit
    void GenerateTileEntities(float scale);

    // initializes tile entities with the state loaded by the serializer, used by the serializer
    void InitializeTileEntities();
    // save loading

    //get the tile at a specific index
    Tile *getTileAt(int x, int z);

    Tile *getTileAt(Vector2Int index);

    //set the tile at a specific index
    void setTileAt(int x, int z, Tile *tile);

    void setTileAt(Vector2Int index, Tile *tile);


    void removeTileAt(int x, int z);

    void removeTileAt(Vector2Int index);
    
    //get the tile at a specific index
    Chunk *getChunkAt(int x, int z);

    Chunk *getChunkAt(Vector2Int index);
    
    int CalculateOptimalChunkSize(int widith, int height);

    //get the tile at a specific world position
    [[nodiscard]] const glm::vec3 GridToWorldPosition(Vector2Int index) const;

    [[nodiscard]] const glm::vec3 GridToWorldPosition(int x, int z) const;

    //get the index of a tile in specific world position
    [[nodiscard]] Vector2Int WorldToGridPosition(Vector3 position) const;

    //loads and distributes the tile entities in world space
    void LoadTileEntities(float scale);

    void DestroyWallsOnTile(Vector2Int tileIndex);

    void ClearAllWallData();

    void SetUpWalls();
    void SetUpChunks();

    void ClearWalls();

    void SetUpWall(Tile *tile);
    void UpdateFogData(Tile *tile);

    void ClearWall(Tile *tile);

    //system methods
    void addComponent(void *component) override;

    void removeComponent(void *component) override;

    const std::type_index *getComponentTypes() override;

    int getNumComponentTypes() override;
    void registerComponents() override{};

    void showImGuiDetailsImpl(Camera *camera) override;

    bool isInBounds(Vector2Int anInt);

    std::vector<Tile*> GetNeighbours(Vector2Int gridpos);

private:
    float offsetX = 0;
    float offsetZ = 0;
    int visibilityRange = 3;
    std::array<std::type_index, 1> componentTypes = {
            std::type_index(typeid(Tile))
    };

    Entity * SpawnUnit(Vector2Int gridPos, bool isAlly);
};


#endif //ZTGK_GRID_H
