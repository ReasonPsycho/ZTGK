// 
// Created by igork on 09.06.2024. 
// 
 
#ifndef ZTGK_MININGSYSTEM_H 
#define ZTGK_MININGSYSTEM_H 
#include "ECS/System.h" 
#include "ECS/Gameplay/Pranium.h" 
#include "ECS/Unit/Mining/MineableChest.h" 
#include "ECS/Unit/Mining/IMineable.h" 
 
class MiningSystem : public System { 
public: 
    MiningSystem(); 
    ~MiningSystem() override = default; 
 
    void addComponent(void* component) override; 
    void removeComponent(void* component) override; 
    const std::type_index* getComponentTypes() override; 
    int getNumComponentTypes() override; 
    void registerComponents() override; 
 
    void showImGuiDetailsImpl(Camera *camera) override; 
 
    void UpdateImpl() override; 
 
 
    std::vector<Pranium*> praniumComponents; 
    std::vector<MineableChest*> mineableChestComponents; 
    std::vector<IMineable*> mineableComponents; 
 
private: 
    std::array<std::type_index, 3> componentTypes = { 
        std::type_index(typeid(Pranium)), 
        std::type_index(typeid(MineableChest)), 
        std::type_index(typeid(IMineable)) 
    }; 
}; 
 
 
#endif //ZTGK_MININGSYSTEM_H 
