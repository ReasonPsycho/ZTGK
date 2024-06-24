//
// Created by igork on 23.05.2024.
//

#ifndef ZTGK_WASHINGMACHINE_H
#define ZTGK_WASHINGMACHINE_H

#include "ECS/System.h"
#include "WashingMachineTile.h"
#include "ECS/Audio/Speaker.h"

class WashingMachine : public System{
public:
    WashingMachine(int praniumNeeded, int radiusToClearEveryMilestone);
    ~WashingMachine() override = default;

    void addComponent(void* component) override;
    void removeComponent(void* component) override;
    const std::type_index* getComponentTypes() override;
    int getNumComponentTypes() override;
    void registerComponents() override;

    void showImGuiDetailsImpl(Camera *camera) override;

    void createWashingMachine(Model* model);

    Model* model;

    std::unordered_map<unsigned, std::vector<WashingMachineTile*>> WashingMachineTiles;

    int praniumNeeded;
    int currentPranium = 0;
    int radiusToClear = 8;

    std::vector<Tile*> getTilesToClearInRaiuds(Vector2Int position, int radius);
    std::vector<Tile*> getAllTilesWithDirtyFloorInRadius(Vector2Int position, int radius);
    void clearNextTile_walls();
    void clearNextTile_floors();
    void onPraniumDelivered();


private:
    void UpdateImpl() override;
    std::array<std::type_index, 1> componentTypes = {
        std::type_index(typeid(WashingMachineTile))
    };

    std::vector<Tile*> tilesToClear_walls;
    std::vector<Tile*> tilesToClear_floors;

    std::vector<Tile*> sortInSpiralPattern(std::vector<Tile*> tiles, Vector2Int position);

    float maxSwayAngle = 0.0f;
    float swaySpeed = 0.0f;
    float currentSwayAngle = 0.0f;
    int swayDirection = 1;
    float swayHeight = 0.0f;
    Speaker* speaker;
};


#endif //ZTGK_WASHINGMACHINE_H
