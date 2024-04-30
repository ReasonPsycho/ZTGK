//
// Created by igork on 24.03.2024.
//

#include "IMineable.h"

#include "ECS/SignalQueue/SignalReceiver.h"
#include "ECS/Utils/Time.h"
#include "ECS/HUD/Components/Text.h"
#include "ECS/Entity.h"

IMineable::IMineable(float timeToMine, Vector2Int gridPosition, Grid* grid) {
    this->name = "IMineable";
    this->gridPosition = gridPosition;
    this->grid = grid;
    this->timeToMine = timeToMine;
    this->timeToMineRemaining = timeToMine;
}

void IMineable::Mine() {
    timeToMineRemaining -= Time::Instance().DeltaTime();
    spdlog::info(timeToMineRemaining);
    if (timeToMineRemaining<=0) {
        grid->DestroyWallsOnTile(gridPosition);
        getEntity()->removeComponentFromMap(std::make_unique<IMineable>(this));
    }
}

void IMineable::UpdateImpl() {

}

void IMineable::showImGuiDetailsImpl(Camera *camera) {
    ImGui::Text("Time to mine: %f", timeToMine);
    ImGui::Text("Time to mine remaining: %f", timeToMineRemaining);

}

IMineable::IMineable(IMineable *pMineable) {
    this->name = "IMineable";
    this->gridPosition = pMineable->gridPosition;
    this->grid = pMineable->grid;
    this->timeToMine = pMineable->timeToMine;
    this->timeToMineRemaining = pMineable->timeToMineRemaining;

}
