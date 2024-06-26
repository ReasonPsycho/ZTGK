//
// Created by igork on 20.03.2024.
//

#include "Tile.h"
#include "ECS/Utils/Util.h"
#include <utility>
#include "ECS/Unit/Unit.h"
#include "ECS/Grid/Chunk.h"
#include "ECS/Render/Components/BetterSpriteRender.h"
#include "ECS/Utils/CooldownComponentXDD.h"


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

void Tile::changeWallsSelection(TileHighlightState state) {
    for(auto wall : walls){
        wall->data[2] = state;
    }
}

void Tile::setHighlight(TileHighlightState state) {
    changeWallsSelection(state);
    tileHighlightState = state;
}

TileHighlightState Tile::getTileSelectionState() {
    return tileHighlightState;
}

void Tile::changeDirtinessLevel(float newDirtLevel) {
    dirtinessLevel = newDirtLevel;
    for(auto wall : walls){
        wall->data[0] = dirtinessLevel;
    }
}

void Tile::changeWallsFogOfWarState(bool isInFogOfWar) {
    for(auto wall : walls){
        wall->data[1] = isInFogOfWar;
    }
}

void Tile::tryToSendBubble() {
    ztgk::game::EMOTES bubble1 = ztgk::game::EMOTES::CLEAN_BUBBLE1;
    ztgk::game::EMOTES bubble2 = ztgk::game::EMOTES::CLEAN_BUBBLE2;

    if (getEntity()->getChild("Emote") == nullptr) {
        ztgk::game::scene->addEntity(getEntity(), "Emote");
    }
    auto emoChild = getEntity()->getChild("Emote");

    if (emoChild->getComponent<BetterSpriteRender>() == nullptr) {
        emoChild->addComponent(std::make_unique<BetterSpriteRender>(ztgk::game::emotes.at(RNG::RandomBool() ? bubble1 : bubble2).get() , 4));
        //emoChild->getComponent<BetterSpriteRender>()->isInFogOfWar = this->isInFogOfWar;
    }
    else if(emoChild->getComponent<BetterSpriteRender>() != nullptr && emoChild->getComponent<BetterSpriteRender>()->toBeDeleted) {
        emoChild->removeComponentFromMap(emoChild->getComponent<BetterSpriteRender>());
    }
}

void Tile::UpdateImpl() {
    tryToSendBubble();
}

void Tile::setHighlightPresetFromState() {
    switch (state) {
        case CHEST:
            setHighlight(HIGHLIGHT_ITEM_GOLD);
            break;
        case ORE:
            setHighlight(HIGHLIGHT_ITEM_GOLD);
            break;
        default: break; // do not change existing state
    }
}


