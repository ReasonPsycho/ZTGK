//
// Created by igork on 23.05.2024.
//

#include "WashingMachine.h"
#include <imgui.h>
#include "ECS/Utils/Globals.h"
#include "ECS/Render/Components/Render.h"
#include "ECS/Render/ModelLoading/Model.h"
#include "ECS/Entity.h"
#include "ECS/HUD/HUD.h"

WashingMachine::WashingMachine(int praniumNeeded, int radiusToClearEveryMilestone) {
    name = "WashingMachine";
    this->praniumNeeded = praniumNeeded;
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
    for (auto& [id, tiles] : WashingMachineTiles) {
        for (auto& tile : tiles) {
            ImGui::Text("Tile: %s", tile->name.c_str());
        }
        ImGui::Separator();
    }
    ImGui::End();
}

void WashingMachine::UpdateImpl() {
    if(!tilesToClear_walls.empty()){
        clearNextTile_walls();
    }
    if(!tilesToClear_floors.empty()){
        clearNextTile_floors();
        if(!tilesToClear_floors.empty())
            clearNextTile_floors();
    }


    if(!ztgk::game::enableWashingMachineSwaying) { return;}
    // Sway washing machine by changing its rotation and y position
    auto machineEntity = ztgk::game::scene->getChild("WashingMachine");

    currentSwayAngle += swaySpeed * swayDirection;
    if (currentSwayAngle > maxSwayAngle || currentSwayAngle < -maxSwayAngle) {
        swayDirection *= -1;
        currentSwayAngle = glm::clamp(currentSwayAngle, -maxSwayAngle, maxSwayAngle); // Ensure the angle doesn't exceed max limits
    }

    if (machineEntity != nullptr) {
        glm::quat machineRotation = machineEntity->transform.getLocalRotation();
        glm::vec3 machinePosition = machineEntity->transform.getLocalPosition();

        // Correct the quaternion update for rotation
        float swayAngleRadians = glm::radians(currentSwayAngle);
        glm::quat rotationChange = glm::angleAxis(swayAngleRadians, glm::vec3(1.0f, 0.0f, 0.0f)); // Sway around x-axis
        glm::quat newRotation = rotationChange * machineRotation;

        // Apply the rotation and adjust the y position based on sway
        machineEntity->transform.setLocalRotation(newRotation);
        machineEntity->transform.setLocalPosition(
                glm::vec3(machinePosition.x, machinePosition.y + swayHeight * std::sin(swayAngleRadians*2), machinePosition.z));

        machineEntity->updateSelfAndChild();
    }

}

std::vector<Tile*> WashingMachine::getTilesToClearInRaiuds(Vector2Int position, int radius) {
//    auto grid = ztgk::game::scene->systemManager.getSystem<Grid>();
//    for (int x = position.x - radius; x<= position.x + radius; ++x){
//        for (int z = position.z - radius; z<= position.z + radius; z++){
//            int dx = x - position.x;
//            int dz = z - position.z;
//            if(dx*dx + dz*dz <= radius*radius){
//                auto tile= grid->getTileAt(x, z);
//                if(tile != nullptr){
//                    if(tile->state == TileState::WALL) {
//                        tile->state = TileState::FLOOR;
//                        grid->SetUpWall(tile);
//                        auto neigh = grid->GetNeighbours(tile->index);
//                        for(auto n : neigh){
//                            if(n != nullptr){
//                                grid->SetUpWall(n);
//                            }
//                        }
//                        tile->isInFogOfWar = false;
//                        grid->UpdateFogData(tile);
//                    }
//                    tile->changeDirtinessLevel(0);
//                }
//            }
//        }
//    }
//^^^^^^^^^^^^^^^^ legacy code
    auto grid = ztgk::game::scene->systemManager.getSystem<Grid>();
    std::vector<Tile*> tiles;
    for (int x = position.x - radius; x<= position.x + radius; ++x){
        for (int z = position.z - radius; z<= position.z + radius; z++){
            int dx = x - position.x;
            int dz = z - position.z;
            if(dx*dx + dz*dz <= radius*radius){
                auto tile= grid->getTileAt(x, z);
                if(tile != nullptr && tile->state == TileState::WALL){
                    tiles.push_back(tile);
                }
            }
        }
    }

    return tiles;

}

void WashingMachine::onPraniumDelivered() {
    currentPranium++;
    spdlog::debug("\n Pranium delivered, current: {}/{} \n", currentPranium, praniumNeeded);

    if(currentPranium >= praniumNeeded){
        auto hud = ztgk::game::scene->systemManager.getSystem<HUD>();
        hud->getGroupOrDefault(ztgk::game::ui_data.gr_game)->setHidden(true);
        hud->getGroupOrDefault(ztgk::game::ui_data.gr_menu)->setHidden(false);
        hud->getGroupOrDefault(ztgk::game::ui_data.gr_game_won)->setHidden(false);

        ztgk::game::audioManager->playSound("win");
        ztgk::game::gameWon = true;
    }



    auto newTilesToClear_walls = getTilesToClearInRaiuds(Vector2Int(50, 50), radiusToClear);
    for(auto tile : newTilesToClear_walls){
        tilesToClear_walls.push_back(tile);
    }
    tilesToClear_walls = sortInSpiralPattern(tilesToClear_walls, Vector2Int(50, 50));
    auto newTilesToClear_floors = getAllTilesWithDirtyFloorInRadius(Vector2Int(50, 50), radiusToClear);
    for(auto tile : newTilesToClear_floors){
        tilesToClear_floors.push_back(tile);
    }
    tilesToClear_floors = sortInSpiralPattern(tilesToClear_floors, Vector2Int(50, 50));

    radiusToClear *= 1.3f;
    maxSwayAngle += .5f;
    swaySpeed += 0.2f;
    swayHeight += 1.f;

    if(currentPranium > 0){
        if(!ztgk::game::audioManager->isSoundPlaying("sfx_pralka1"))
            speaker->PlaySound("sfx_pralka1", -1);
    }

    if(currentPranium > 2){
        ztgk::game::audioManager->stopSound("sfx_pralka1");
        if(!ztgk::game::audioManager->isSoundPlaying("sfx_pralka2"))
            speaker->PlaySound("sfx_pralka2", -1);

    }



}

void WashingMachine::createWashingMachine(Model* model) {
    std::vector<Vector2Int> tilePositions;
    if(WashingMachineTiles[uniqueID].empty()){
        spdlog::error("No tiles for washing machine");
        return;
    }

    for(auto tile : WashingMachineTiles[uniqueID]){
        tilePositions.push_back(tile->gridPosition);
    }

    //get position of center tile
    Vector2Int cornerTile = tilePositions[0];
    for(auto tile : tilePositions){
        if(tile.x < cornerTile.x){
            cornerTile.x = tile.x;
        }
        if(tile.z < cornerTile.z){
            cornerTile.z = tile.z;
        }
    }
    Vector2Int centerTileGridPos = cornerTile + Vector2Int(2, 2);

    auto centerTileWorldPos = ztgk::game::scene->systemManager.getSystem<Grid>()->GridToWorldPosition(centerTileGridPos);


    auto machineEntity = ztgk::game::scene->getChild("WashingMachine");
    if(machineEntity != nullptr){
        machineEntity->Destroy();
        delete machineEntity;
    }
    if(machineEntity == nullptr){
        machineEntity = ztgk::game::scene->addEntity("WashingMachine");
    }

    machineEntity->addComponent(std::make_unique<Render>(model));

    machineEntity->transform.setLocalPosition(glm::vec3(centerTileWorldPos.x - 4.5f,4,centerTileWorldPos.z));
    machineEntity->transform.setLocalScale(glm::vec3(2.7, 3, 2.7));
    machineEntity->transform.setLocalRotation(glm::vec3(glm::radians(0.0f), glm::radians(-90.0f), glm::radians(0.f)));
    machineEntity->updateSelfAndChild();

    machineEntity->addComponent(std::make_unique<BoxCollider>(machineEntity, glm::vec3(5,5,5), WASHING_MACHINE));

    machineEntity->addComponent(std::make_unique<Speaker>());
    speaker = machineEntity->getComponent<Speaker>();
}

void WashingMachine::clearNextTile_walls() {
    if(tilesToClear_walls.empty()) {
        return;
    }

    auto tile = tilesToClear_walls[0];
    tilesToClear_walls.erase(tilesToClear_walls.begin());
    tile->state = TileState::FLOOR;
    auto grid = ztgk::game::scene->systemManager.getSystem<Grid>();
    grid->SetUpWall(tile);

    auto neigh = grid->GetNeighbours(tile->index);
    for(auto n : neigh) {
        if(n != nullptr && n->state == TileState::WALL) {
            grid->SetUpWall(n);
        }
    }

    auto mineable = grid->getTileAt(tile->index)->getEntity()->getComponent<IMineable>();
    if(mineable != nullptr){
        mineable->isMined = true;
    }
    tile->isInFogOfWar = false;
    grid->UpdateFogData(tile);
    tile->changeDirtinessLevel(0);
}

std::vector<Tile *> WashingMachine::getAllTilesWithDirtyFloorInRadius(Vector2Int position, int radius) {
    auto grid = ztgk::game::scene->systemManager.getSystem<Grid>();
    std::vector<Tile*> tiles;
    for (int x = position.x - radius; x<= position.x + radius; ++x){
        for (int z = position.z - radius; z<= position.z + radius; z++){
            int dx = x - position.x;
            int dz = z - position.z;
            if(dx*dx + dz*dz <= radius*radius){
                auto tile= grid->getTileAt(x, z);
                if(tile != nullptr && tile->dirtinessLevel>0){
                    tiles.push_back(tile);
                }
            }
        }
    }

    return tiles;
}

void WashingMachine::clearNextTile_floors() {
    if(tilesToClear_floors.empty()) {
        return;
    }
    auto tile = tilesToClear_floors[0];
    tilesToClear_floors.erase(tilesToClear_floors.begin());
    tile->changeDirtinessLevel(0);
}

std::vector<Tile*> WashingMachine::sortInSpiralPattern(std::vector<Tile*> tiles, Vector2Int position) {
    // Custom comparator for sorting in spiral order
    auto spiralComparator = [position](Tile* a, Tile* b) {
        Vector2Int relA = a->index - position;
        Vector2Int relB = b->index - position;

        // Calculate Manhattan distances
        int distA = std::abs(relA.x) + std::abs(relA.z);
        int distB = std::abs(relB.x) + std::abs(relB.z);

        if (distA != distB) {
            return distA < distB;
        }

        // Calculate angles
        double angleA = std::atan2(relA.z, relA.x);
        double angleB = std::atan2(relB.z, relB.x);

        return angleA < angleB;
    };

    std::sort(tiles.begin(), tiles.end(), spiralComparator);

    return tiles;
}


