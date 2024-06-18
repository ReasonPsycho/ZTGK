#ifndef ZTGK_TILE_H
#define ZTGK_TILE_H

#include "ECS/Utils/VectorUtils.h"
#include "ECS/Component.h"

class Unit;
class Chunk;

struct WallData {
    glm::mat4x4 matrix;
    int data[4]{}; // for textures on x for example
    int textures[4]{}; // for textures on x for example

    // Constructor
    WallData(const glm::mat4x4 &matrixInput, int d1, int d2, int d3, int d4,int t1, int t2, int t3, int t4)
            : matrix(matrixInput) {
        data[0] = d1; //Dirtness 0-100
        data[1] = d2; //Is in fog of war
        data[2] = d3;
        data[3] = d4;
        textures[0] = t1; // diffuse
        textures[1] = t2; // specular
        textures[2] = t3; // normal
        textures[3] = t4; // depth
    }
};

enum TileState {
    FLOOR,
    WALL,
    CHEST,
    ORE,
    CORE,   // washing machine
    SPONGE,
    BUG,
    SHROOM,
    state_count // for ImGui
};

enum TileSelectionState {
    NOT_SELECTED,
    POINTED_AT,
   SELECTED //lol
};

// initializer list
#define TILE_STATE_NAMES { "FLOOR", "WALL", "CHEST", "ORE", "CORE", "SPONGE", "BUG", "SHROOM" }

struct TileStateData {
    // this is only necessary if items are serialized as numbers, if they're saved in the node instead it can be loaded straight into the relevant entity
    unsigned chestItemTypeId = (unsigned)-1;
};

class Tile : public Component{
public:
    Vector2Int index{};
    std::vector<WallData*> walls;
    TileState state;
    TileStateData stateData;
    Unit* unit = nullptr;
    Chunk* chunk = nullptr;
    bool isInFogOfWar = false;
    float dirtinessLevel = 100;
    void setTileSelectionState(TileSelectionState state );
    TileSelectionState getTileSelectionState();
    // Constructors
    explicit Tile(Vector2Int index, Chunk* chunkPtr = nullptr, TileState state = FLOOR, std::string name = "Tile");
    Tile(int index_x, int index_z, Chunk* chunkPtr = nullptr, TileState state = FLOOR, std::string name = "Tile");
    Tile() = default;
    
    // Destructor
    ~Tile();

    // Methods
    [[nodiscard]] bool vacant() const { return state == FLOOR; };
    void showImGuiDetailsImpl(Camera *camera) override;
    void changeWallsSelection(TileSelectionState state);
    void changeWallsFogOfWarState(bool isInFogOfWar);
    void changeDirtinessLevel(float newDirtLevel);
    
    constexpr static const char * state_names[] = TILE_STATE_NAMES;

    
private:
    TileSelectionState tileSelectionState = NOT_SELECTED;
};

#endif //ZTGK_TILE_H
