//
// Created by igork on 23.05.2024.
//

#ifndef ZTGK_WASHINGMACHINE_H
#define ZTGK_WASHINGMACHINE_H

#include "ECS/System.h"
#include "WashingMachineTile.h"

class WashingMachine : public System{
public:
    WashingMachine(int praniumNeeded, int praniumNeededToMilestone, int radiusToClearEveryMilestone);
    ~WashingMachine() override = default;

    void addComponent(void* component) override;
    void removeComponent(void* component) override;
    const std::type_index* getComponentTypes() override;
    int getNumComponentTypes() override;
    void registerComponents() override;

    void showImGuiDetailsImpl(Camera *camera) override;

    std::unordered_map<unsigned, std::vector<WashingMachineTile*>> WashingMachineTiles;

    int praniumNeeded;
    int praniumNeededToMilestone;
    int radiusToClearEveryMilestone;

    void clearTilesInRadius(Vector2Int position, int radius);


private:
    void UpdateImpl() override;
    std::array<std::type_index, 1> componentTypes = {
        std::type_index(typeid(WashingMachineTile))
    };

    int currentPranium = 0;

};


#endif //ZTGK_WASHINGMACHINE_H
