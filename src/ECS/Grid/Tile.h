#ifndef ZTGK_TILE_H
#define ZTGK_TILE_H

#include "ECS/Utils/VectorUtils.h"
#include "ECS/Component.h"

struct WallData {
    glm::mat4x4 matrix;

    // Constructor
    WallData(const glm::mat4x4 &matrixInput) : matrix(matrixInput) {}
};

enum TileState {
    FLOOR,
    WALL,
    CHEST,
    ORE,
    CORE,   // washing machine
    UNIT,
    state_count
};
// initializer list
#define TILE_STATE_NAMES { "FLOOR", "WALL", "CHEST", "ORE", "CORE", "UNIT" }

struct TileStateData {
    unsigned unitId = (unsigned)-1;
    unsigned chestItemTypeId = (unsigned)-1;
};

class Tile : public Component{
public:
    Vector2Int index{};
    std::vector<WallData> walls;
    bool vacant;
    TileState state;
    TileStateData stateData;

    // Constructors
    explicit Tile(Vector2Int index, bool vacant = true, std::string name = "Tile");
    Tile(int index_x, int index_z, bool vacant = true, std::string name = "Tile");
    Tile() = default;
    
    // Destructor
    ~Tile();

    // Methods
    void showImGuiDetails(Camera *camera) override;
    constexpr static const char * state_names[] = TILE_STATE_NAMES;
};

#endif //ZTGK_TILE_H
