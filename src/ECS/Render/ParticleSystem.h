//
// Created by redkc on 26/06/2024.
//

#ifndef SCRUB_SQUAD_PARTICLESYSTEM_H
#define SCRUB_SQUAD_PARTICLESYSTEM_H


#include "ECS/Render/Camera/Camera.h"
#include "ECS/System.h"
#include "ECS/Render/Components/ParticleEmiter.h"
#include "ECS/Grid/Tile.h"


class ParticleSystem : public System{
public:
    ParticleSystem();
    void Innit();
    void registerComponents() override{};
    void addComponent(void* component) override;
    void removeComponent(void* component) override;
    void showImGuiDetailsImpl(Camera *camera) override;
    void UpdateImpl() override;
    const std::type_index* getComponentTypes() override {return componentTypes.data(); };
    int getNumComponentTypes() override { return 1;};
    
    std::vector<ParticleEmiter*> particleEmitters;
    std::vector<ParticleData> particlesData;
    GLuint particleBuffer;
    GLuint particleBufferBasePoint = 10;

private:
    std::array<std::type_index, 1> componentTypes = {
            std::type_index(typeid(ParticleEmiter)) 
    };
    void get_Tiles_to_emmit();
    std::vector<Tile*> tiles_to_emmit;
    float particle_cooldown = 0;
};


#endif //SCRUB_SQUAD_PARTICLESYSTEM_H
