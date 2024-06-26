//
// Created by redkc on 26/06/2024.
//
#include "ECS/SystemManager.h"
#include "ParticleSystem.h"
#include "ECS/Render/Pipelines/Phong/PhongPipeline.h"

void ParticleSystem::UpdateImpl() {
    particle_cooldown += Time::Instance().DeltaTime();
    if(particle_cooldown > 2){
        particle_cooldown = 0;
        get_Tiles_to_emmit();
        for(auto tile: tiles_to_emmit){
            if(tile->dirtinessLevel == 0){
                tile->tryToSendParticle(RNG::RandomBool()? 3 : 4);
            }
        }
    }


    glBindBuffer(GL_SHADER_STORAGE_BUFFER, particleBuffer);
    auto* ptr = static_cast<ParticleData*>(glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY));

    for(int i = 0; i < particlesData.size(); ++i)
    {
        particlesData[i] = ptr[i];
    }

    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    for(int i = 0; i < particlesData.size(); ++i)
    {
        if(particlesData[i].position.w > particlesData[i].rotation.w){
            particlesData.erase(particlesData.begin() + i);
            --i;
        }
    }
    
    for (auto particleEmiter: particleEmitters) {
        while (!particleEmiter->particlesToPush.empty()){
            particlesData.push_back(particleEmiter->particlesToPush.back());
            particleEmiter->particlesToPush.pop_back();
        }
    }

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, particleBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, particlesData.size() * sizeof(ParticleData), particlesData.data(), GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, particleBufferBasePoint, particleBuffer);
    
    systemManager->getSystem<PhongPipeline>()->particle.use();
    systemManager->getSystem<PhongPipeline>()->particle.setFloat("deltaTime", Time::Instance().DeltaTime());
    glDispatchCompute(particlesData.size(), 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void ParticleSystem::showImGuiDetailsImpl(Camera *camera) {

}

void ParticleSystem::removeComponent(void *component) {
    auto component_iter = std::find(particleEmitters.begin(), particleEmitters.end(), reinterpret_cast<ParticleEmiter *const>(component));

    if (component_iter != particleEmitters.end()) {
        particleEmitters.erase(component_iter);
    }
}

void ParticleSystem::addComponent(void *component) {
    Component *basePtr = static_cast<Component *>(component);

    ParticleEmiter *renderPtr = dynamic_cast<ParticleEmiter *>(basePtr);
    if (renderPtr != nullptr) {
        particleEmitters.push_back(renderPtr);
    }
}

void ParticleSystem::Innit() {
    glGenBuffers(1, &particleBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, particleBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER,0 * sizeof(ParticleData), NULL,
                 GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, particleBufferBasePoint, particleBuffer);
}

ParticleSystem::ParticleSystem() {
name = "ParticleSystem";
}

void ParticleSystem::get_Tiles_to_emmit() {
    tiles_to_emmit.clear();
    for(int i = 100; i> 0; i--){
        auto tile = ztgk::game::scene->systemManager.getSystem<Grid>()->getTileAt({RNG::RandomInt(0, 99), RNG::RandomInt(0, 99)});
        if(tile != nullptr)
            tiles_to_emmit.push_back(tile);
    }
}
