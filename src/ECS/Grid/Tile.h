#ifndef ZTGK_TILE_H
#define ZTGK_TILE_H

#include "ECS/Utils/VectorUtils.h"
#include "ECS/Component.h"


struct WallData {
    glm::mat4x4 matrix;
    int data[4]{}; // for textures on x for exaple

    // Constructor
    WallData(const glm::mat4x4 &matrixInput, int d1, int d2, int d3, int d4)
            : matrix(matrixInput) {
        data[0] = d1;
        data[1] = d2;
        data[2] = d3;
        data[3] = d4;
    }
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
