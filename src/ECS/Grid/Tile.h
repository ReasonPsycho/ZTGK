#ifndef ZTGK_TILE_H
#define ZTGK_TILE_H

#include "ECS/Utils/VectorUtils.h"
#include "ECS/Component.h"


struct WallData {
    glm::mat4x4 matrix;
    int data[4]{}; // for textures on x for example

    // Constructor
    WallData(const glm::mat4x4 &matrixInput, int d1, int d2, int d3, int d4)
            : matrix(matrixInput) {
        data[0] = d1;
        data[1] = d2;
        data[2] = d3;
        data[3] = d4;
    }
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
