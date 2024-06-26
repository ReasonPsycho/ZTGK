//
// Created by igork on 20.03.2024.
//

#include "Tile.h"
#include "ECS/Utils/Util.h"
#include <utility>
#include "ECS/Unit/Unit.h"
#include "ECS/Grid/Chunk.h"
#include "ECS/Render/Components/BetterSpriteRender.h"
#include "ECS/SignalQueue/Signal.h"
#include "ECS/SignalQueue/DataCargo/TestSignalData.h"
#include "ECS/SignalQueue/SignalQueue.h"
#include "ECS/Render/Components/ParticleEmiter.h"


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
    tileHighlightState = state;

    if (overrideState != CLEAR)
        return;

    changeWallsSelection(state);
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
        emoChild->getComponent<BetterSpriteRender>()->isInFogOfWar = this->isInFogOfWar;
    }
    else if(emoChild->getComponent<BetterSpriteRender>() != nullptr && emoChild->getComponent<BetterSpriteRender>()->toBeDeleted) {
        emoChild->removeComponentFromMap(emoChild->getComponent<BetterSpriteRender>());
    }
}

void Tile::UpdateImpl() {
    if(isInFogOfWar) tryToSendBubble();
}

void Tile::setHighlightPresetFromState() {
    if (overrideState != CLEAR)
        return;

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

void Tile::setHighlightOverride(TileHighlightState state, float time_sec) {
    auto oldstate = tileHighlightState;
    // do this to setup wall highlights
    overrideState = CLEAR;
    setHighlight(state);
    // do this to set the tileHighlightState to previous (if there is no external change in the meantime, this will be returned to)
    overrideState = state;
    setHighlight(oldstate);

    if (state != CLEAR) {
        auto signal = TestSignalData::signal();
        signal.time_to_live = time_sec * 1000.0f;
        signal.callback = [this, state]() {
            // only reset if the current state matches this assignment, otherwise assume it was overridden in the meantime and responsibility is passed to the new signal
            if (overrideState == state) {
                overrideState = CLEAR;
                setHighlight(tileHighlightState);
            }
        };

        *ztgk::game::signalQueue += signal;
    }
//
//    getEntity()->addComponent(std::make_unique<CooldownComponentXDD>(time_sec, [this](){
//        overrideState = CLEAR;
//        setHighlightPresetFromState();
//    }));
}

void Tile::tryToSendParticle(int particle_type, float y) {
    auto particle_emiter = getEntity()->getComponent<ParticleEmiter>();
    if(particle_emiter == nullptr){
        getEntity()->addComponent(std::make_unique<ParticleEmiter>());
        particle_emiter = getEntity()->getComponent<ParticleEmiter>();
    }
    particle_emiter->EmitParticle(1,1,particle_type,
                                  glm::vec3(0 + RNG::RandomFloat(-.5f, .5f), 0,0 + RNG::RandomFloat(-.5f, .5f)),
                                  0, glm::vec4(0, RNG::RandomInt(0, 90), 0,1), glm::vec4(0.5), glm::vec4(0,1,0,1), glm::vec4(1));
    //send 2nd particle sometimes
    if(RNG::RandomBool()){
        particle_emiter->EmitParticle(1,1,particle_type,
                                      glm::vec3(0 + RNG::RandomFloat(-.5f, .5f), y,0 + RNG::RandomFloat(-.5f, .5f)),
                                      0, glm::vec4(0, RNG::RandomInt(0, 90), 0,1), glm::vec4(0.5), glm::vec4(0,1,0,1), glm::vec4(1));
    }

}


