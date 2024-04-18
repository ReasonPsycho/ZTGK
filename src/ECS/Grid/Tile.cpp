//
// Created by igork on 20.03.2024.
//

#include "Tile.h"
#include "ECS/Utils/Util.h"
#include <utility>


Tile::~Tile() {
    vacant = true;
    //delete this;
}

Tile::Tile(Vector2Int index, bool vacant, std::string name){
    this->index = index;
    this->vacant = vacant;
    this->name = std::move(name);
}

Tile::Tile(int index_x, int index_z, bool vacant, std::string name) {
    this->index = Vector2Int(index_x, index_z);
    this->vacant = vacant;
    this->name = std::move(name);
}

void Tile::showImGuiDetails(Camera *camera) {
    ImGui::Text("Index: (%d, %d)", index.x, index.z);
    ImGui::Checkbox("Vacant", &vacant);

}

