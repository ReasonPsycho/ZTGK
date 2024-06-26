//
// Created by redkc on 26/06/2024.
//
#include "ECS/SystemManager.h"
#include "ParticleSystem.h"
#include "ECS/Render/Pipelines/Phong/PhongPipeline.h"

void ParticleSystem::UpdateImpl() {
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
