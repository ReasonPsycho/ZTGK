//
// Created by igork on 20.03.2024.
//

#include "Tile.h"
#include "ECS/Utils/Util.h"
#include <utility>
#include "ECS/Unit/Unit.h"
#include "ECS/Grid/Chunk.h"

Tile::~Tile() {
    //delete this;
}

Tile::Tile(Vector2Int index, Chunk* chunk, TileState state, std::string ) {
    this->index = index;
    this->state = state;
    this->name = std::move(name);
    this->chunk = chunk;
}

Tile::Tile(int index_x, int index_z, Chunk* chunk, TileState state, std::string name) {
    this->index = Vector2Int(index_x, index_z);
    this->state = state;
    this->name = std::move(name);
    this->chunk = chunk;
}

void Tile::showImGuiDetailsImpl(Camera *camera) {
    ImGui::Text("Index: (%d, %d)", index.x, index.z);
    ImGui::Text("%s", std::format("Vacant? {}", vacant() ? "YES" : "NO").c_str());

    int state_select = state;
    ImGui::Combo("State", &state_select, state_names, state_count);
    state = (TileState)state_select;
}

void Tile::changeHitWallsState(TileSelectionState state) {
    for(auto wall : walls){
        wall->data[2] = state;
    }
}

void Tile::setTileSelectionState(TileSelectionState state) {
    changeHitWallsState(state);
    tileSelectionState = state;
}

TileSelectionState Tile::getTileSelectionState() {
    return tileSelectionState;
}


