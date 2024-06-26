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

enum TileHighlightState {
    CLEAR,
    SELECTION_LMB_GREEN,
    SELECTION_RMB_BLUE,
    MOVE_ORDER_YELLOW,
    HIGHLIGHT_ENEMY_RED,
    HIGHLIGHT_ITEM_GOLD,
    EXPLOSION_LIGHT_BLUE,
    HEAL_LIGHT_GREEN,
    DAMAGE_LIGHT_RED,
    HIGHLIGHT_RANGE_V_LIGHT_BLUE,
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
    void setHighlight(TileHighlightState state);
    void setHighlightOverride(TileHighlightState state, float time_sec);
    TileHighlightState getTileSelectionState();
    // Constructors
    explicit Tile(Vector2Int index, Chunk* chunkPtr = nullptr, TileState state = FLOOR, std::string name = "Tile");
    Tile(int index_x, int index_z, Chunk* chunkPtr = nullptr, TileState state = FLOOR, std::string name = "Tile");
    Tile() = default;
    
    // Destructor
    ~Tile();

    // Methods
    [[nodiscard]] bool vacant() const { return state == FLOOR; };
    void showImGuiDetailsImpl(Camera *camera) override;
    void changeWallsSelection(TileHighlightState state);
    void changeWallsFogOfWarState(bool isInFogOfWar);
    void changeDirtinessLevel(float newDirtLevel);

    void setHighlightPresetFromState();

    void UpdateImpl() override;
    
    constexpr static const char * state_names[] = TILE_STATE_NAMES;


    void tryToSendParticle(int particle_type, float y = 0);
    bool particle_sent = false;

private:
    TileHighlightState tileHighlightState = CLEAR;
    TileHighlightState overrideState = CLEAR;
    void tryToSendBubble();
};

#endif //ZTGK_TILE_H
