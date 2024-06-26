//
// Created by redkc on 26/06/2024.
//

#ifndef SCRUB_SQUAD_PARTICLEEMITER_H
#define SCRUB_SQUAD_PARTICLEEMITER_H


#include "ECS/Render/Camera/Camera.h"
#include "ECS/Component.h"
struct ParticleData{
    int data[4];  // 0 lifeTime(*1000) , 1 time to live, 2 gravity(*100), 3 texture
    glm::vec4 position;
    glm::vec4 rotation;
    glm::vec4 scale;
    glm::vec4 velocity;
    glm::vec4 angularVelocity;
};


class ParticleEmiter : public Component{
public:
    ParticleEmiter();

    void EmitParticle(int timeToLive, int bilborded, int texture, glm::vec3, float gravity, glm::vec4 rotation, glm::vec4 scale, glm::vec4 velocity, glm::vec4 angularVelocity);
    void EmitCircleOfParticles(int timeToLive, int bilborded, int texture, float gravity, glm::vec4 scale, float velocity);
    void EmitBurstOfParticles(int n,int timeToLive, int bilborded, int texture, glm::vec3 position, float gravity, glm::vec4 rotation, glm::vec4 scale, glm::vec4 velocity, glm::vec4 angularVelocity);
    void UpdateImpl() override;
    void showImGuiDetailsImpl(Camera *camera) override;
    
    std::vector<ParticleData> particlesToPush;
};


#endif //SCRUB_SQUAD_PARTICLEEMITER_H
