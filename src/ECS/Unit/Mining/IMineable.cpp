//
// Created by igork on 24.03.2024.
//

#include "IMineable.h"

#include "ECS/SignalQueue/SignalReceiver.h"
#include "ECS/Utils/Time.h"
#include "ECS/HUD/Components/Text.h"
#include "ECS/Entity.h"
#include "ECS/Unit/Unit.h"

IMineable::IMineable(float timeToMine, Vector2Int gridPosition, Grid* grid) {
    this->name = "IMineable";
    this->gridPosition = gridPosition;
    this->grid = grid;
    this->timeToMine = timeToMine;
    this->timeToMineRemaining = timeToMine;
}


void IMineable::Mine(Unit * unit) {

    timeToMineRemaining -= Time::Instance().DeltaTime() * (unit->stats.mine_spd + unit->stats.added.mine_speed);
    //spdlog::info(timeToMineRemaining);
    onMine(unit);

    if (timeToMineRemaining<=0) {
        grid->DestroyWallsOnTile(gridPosition);
        isMined = true;
        onMined(unit);
        parentEntity->getComponent<BoxCollider>()->setCenter(glm::vec3(grid->GridToWorldPosition(gridPosition).x, -2, grid->GridToWorldPosition(gridPosition).z));

    }
}

void IMineable::UpdateImpl() {

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

}
