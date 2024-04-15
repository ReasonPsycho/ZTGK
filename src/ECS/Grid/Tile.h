#ifndef ZTGK_TILE_H
#define ZTGK_TILE_H

#include "ECS/Utils/VectorUtils.h"
#include "ECS/Component.h"

class Tile : public Component{
public:
    Vector2Int index{};
    bool vacant;

    // Constructors
    explicit Tile(Vector2Int index, bool vacant = true, std::string name = "Tile");
    Tile(int index_x, int index_z, bool vacant = true, std::string name = "Tile");
    void showImGuiDetails(Camera *camera) override;
    Tile() = default;

    // Destructor
    ~Tile();
};

#endif //ZTGK_TILE_H
