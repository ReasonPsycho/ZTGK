//
// Created by igork on 23.05.2024.
//

#include "WashingMachine.h"
#include <imgui.h>
#include "ECS/Utils/Globals.h"

WashingMachine::WashingMachine(int praniumNeeded, int praniumNeededToMilestone, int radiusToClearEveryMilestone) {
    name = "WashingMachine";
    this->praniumNeeded = praniumNeeded;
    this->praniumNeededToMilestone = praniumNeededToMilestone;
    this->radiusToClear = radiusToClearEveryMilestone;
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
//    for (auto& [id, tiles] : WashingMachineTiles) {
//        for (auto& tile : tiles) {
//            tile->Update();
//        }
//    }
}

void WashingMachine::clearTilesInRadius(Vector2Int position, int radius) {
    auto grid = ztgk::game::scene->systemManager.getSystem<Grid>();
    for (int x = position.x - radius; x<= position.x + radius; ++x){
        for (int z = position.z - radius; z<= position.z + radius; z++){
            int dx = x - position.x;
            int dz = z - position.z;
            if(dx*dx + dz*dz <= radius*radius){
                auto tile= grid->getTileAt(x, z);
                if(tile != nullptr){
                    if(tile->state == TileState::WALL) {
                        tile->state = TileState::FLOOR;
                    }
                    tile->dirtinessLevel = 0;
                }
            }
        }
    }
}

void WashingMachine::onPraniumDelivered() {
    currentPranium++;

    if(currentPranium >= praniumNeeded){
        //todo finisz gejm
    }


    clearTilesInRadius(Vector2Int(0,0), radiusToClear);
    radiusToClear *= 2;

}

