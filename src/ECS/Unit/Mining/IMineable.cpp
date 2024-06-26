//
// Created by igork on 24.03.2024.
//

#include "IMineable.h"

#include "ECS/SignalQueue/SignalReceiver.h"
#include "ECS/Utils/Time.h"
#include "ECS/HUD/Components/Text.h"
#include "ECS/Entity.h"
#include "ECS/Unit/Unit.h"
#include "MiningSystem.h"
#include "ECS/Render/Components/ParticleEmiter.h"

IMineable::IMineable(float timeToMine, Vector2Int gridPosition, Grid* grid) {
    this->name = "IMineable";
    this->gridPosition = gridPosition;
    this->grid = grid;
    this->timeToMine = timeToMine;
    this->timeToMineRemaining = timeToMine;
    //ztgk::game::scene->systemManager.getSystem<MiningSystem>()->addComponent(this);
}


void IMineable::Mine(Unit * unit) {

    timeToMineRemaining -= Time::Instance().DeltaTime() * (unit->stats.mine_spd + unit->stats.added.mine_speed);
    //spdlog::info(timeToMineRemaining);
    onMine(unit);

    if (timeToMineRemaining<=0) {
        grid->DestroyWallsOnTile(gridPosition);
        isMined = true;
        onMined(unit);
        auto boxcoll = parentEntity->getComponent<BoxCollider>();
        if(boxcoll != nullptr)
            boxcoll->setCenter(glm::vec3(grid->GridToWorldPosition(gridPosition).x, -2, grid->GridToWorldPosition(gridPosition).z));
        else
            spdlog::error("BoxCollider not found in IMineable");
    }
}

void IMineable::UpdateImpl() {
//    auto tile = grid->getTileAt(gridPosition);
//    auto render = getEntity()->getComponent<Render>();
//    if(tile == nullptr || render == nullptr) return;
//    render->isInFogOfWar = tile->isInFogOfWar;
}

void IMineable::showImGuiDetailsImpl(Camera *camera) {
    ImGui::Text("Grid Position: (%d, %d)", gridPosition.x, gridPosition.z);
    ImGui::Text("Time to mine: %f", timeToMine);
    ImGui::Text("Time to mine remaining: %f", timeToMineRemaining);
    if(getEntity() != nullptr)
        ImGui::Text("Parent Entity: %s", getEntity()->name.c_str());
    else
        ImGui::Text("Parent Entity: nullptr");

}

IMineable::IMineable(IMineable *pMineable) {
    this->name = "IMineable";
    this->gridPosition = pMineable->gridPosition;
    this->grid = pMineable->grid;
    this->timeToMine = pMineable->timeToMine;
    this->timeToMineRemaining = pMineable->timeToMineRemaining;
    ztgk::game::scene->systemManager.getSystem<MiningSystem>()->addComponent(this);

}

IMineable::~IMineable() {
    ztgk::game::scene->systemManager.getSystem<MiningSystem>()->removeComponent(this);
}

void IMineable::onMine(Unit *unit) {
    auto particle_emiter = getEntity()->getComponent<ParticleEmiter>();
    if(particle_emiter == nullptr){
        getEntity()->addComponent(std::make_unique<ParticleEmiter>());
    }
    if(particle_cooldown <=0){
        auto tile = grid->getTileAt(gridPosition);
        tile->tryToSendParticle(RNG::RandomBool() ? 8:9, 2);
        particle_cooldown = 0.4f;
    }
    else{
        particle_cooldown -= Time::Instance().DeltaTime();
    }

}
