//
// Created by igork on 24.03.2024.
//

#include "IMineable.h"

#include "ECS/SignalQueue/SignalReceiver.h"
#include "ECS/Utils/Time.h"
#include "ECS/HUD/Components/Text.h"

IMineable::IMineable(float timeToMine, Vector2Int gridPosition, Grid* grid) {
    this->name = "IMineable";
    this->gridPosition = gridPosition;
    this->grid = grid;
    this->timeToMine = timeToMine;
    this->timeToMineRemaining = timeToMine;
}

void IMineable::Mine() {
    spdlog::info("Mining...");
    timeToMineRemaining -= Time::Instance().DeltaTime();
    spdlog::info(timeToMineRemaining);
    spdlog::info("Mining tile at: {0}, {1}", gridPosition.x, gridPosition.z);
    if (timeToMineRemaining<=0) {
        spdlog::info("Mined!");
        grid->DestroyWallsOnTile(gridPosition);
    }
}

void IMineable::Update() {

}

void IMineable::showImGuiDetails(Camera *camera) {
    ImGui::Text("Time to mine: %f", timeToMine);
    ImGui::Text("Time to mine remaining: %f", timeToMineRemaining);

}
