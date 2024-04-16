#ifndef ZTGK_TILE_H
#define ZTGK_TILE_H

#include "ECS/Utils/VectorUtils.h"
#include "ECS/Component.h"

struct WallData {
    glm::mat4x4 matrix;

    // Constructor
    WallData(const glm::mat4x4 &matrixInput) : matrix(matrixInput) {}
};

class Tile : public Component{
public:
    Vector2Int index{};
    std::vector<WallData> walls;
    bool vacant;
    bool isFloor = true;

    // Constructors
    explicit Tile(Vector2Int index, bool vacant = true, std::string name = "Tile");
    Tile(int index_x, int index_z, bool vacant = true, std::string name = "Tile");
    Tile() = default;
    
    // Destructor
    ~Tile();

    // Methods
    void showImGuiDetails(Camera *camera) override;
};

#endif //ZTGK_TILE_H
