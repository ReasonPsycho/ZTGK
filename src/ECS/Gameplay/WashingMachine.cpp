//
// Created by igork on 23.05.2024.
//

#include "WashingMachine.h"
#include <imgui.h>

WashingMachine::WashingMachine(int praniumNeeded, int praniumNeededToMilestone, int radiusToClearEveryMilestone) {
    name = "WashingMachine";
    this->praniumNeeded = praniumNeeded;
    this->praniumNeededToMilestone = praniumNeededToMilestone;
    this->radiusToClearEveryMilestone = radiusToClearEveryMilestone;
}

void WashingMachine::addComponent(void *component) {
    auto tile = (WashingMachineTile*)component;
    WashingMachineTiles[uniqueID].push_back(tile);
}

void WashingMachine::removeComponent(void *component) {
    auto tile = (WashingMachineTile*)component;
    WashingMachineTiles[uniqueID].erase(std::remove(WashingMachineTiles[uniqueID].begin(), WashingMachineTiles[uniqueID].end(), tile), WashingMachineTiles[uniqueID].end());
}

const std::type_index *WashingMachine::getComponentTypes() {
    return componentTypes.data();
}

int WashingMachine::getNumComponentTypes() {
    return componentTypes.size();
}

void WashingMachine::registerComponents() {
    for (auto& [id, tiles] : WashingMachineTiles) {
        for (auto& tile : tiles) {
            tile->uniqueID = id;
        }
    }
}

void WashingMachine::showImGuiDetailsImpl(Camera *camera) {
    ImGui::Begin("Washing Machine");
    ImGui::Text("Tiles: %zu", WashingMachineTiles.size());
    ImGui::End();
}

void WashingMachine::UpdateImpl() {
    if(currentPranium >= praniumNeeded){
        //todo finisz gejm
    }

    for (auto& [id, tiles] : WashingMachineTiles) {
        for (auto& tile : tiles) {
            tile->Update();
        }
    }
}

void WashingMachine::clearTilesInRadius(Vector2Int position, int radius) {
    //todo implement

}

