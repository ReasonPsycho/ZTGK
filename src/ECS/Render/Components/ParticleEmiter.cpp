//
// Created by redkc on 26/06/2024.
//
#include <cstdlib>
#include "ECS/Entity.h"
#include "ParticleEmiter.h"

ParticleEmiter::ParticleEmiter() {
    name = "ParticleEmiter";
}

void ParticleEmiter::UpdateImpl() {
    
}

void ParticleEmiter::showImGuiDetailsImpl(Camera *camera) {
    if (ImGui::Button("Emmit particle")){
        EmitParticle(2, 1, 0, glm::vec3(1), 0, glm::vec4(1), glm::vec4(1), glm::vec4(1), glm::vec4(1));
    }   
    if (ImGui::Button("Emmit circle of particles")){
        EmitCircleOfParticles(5, 1, 0, -1.5, glm::vec4(0.2), 1);
    }
}

void ParticleEmiter::EmitParticle(int timeToLive, int bilborded, int texture, glm::vec3 position, float gravity, glm::vec4 rotation, glm::vec4 scale, glm::vec4 velocity, glm::vec4 angularVelocity) {
    position += getEntity()->transform.getGlobalPosition();
    scale *= glm::vec4(getEntity()->transform.getGlobalScale(),1);
    glm::vec4 inputPosition = glm::vec4 (position.x,position.y,position.z,0);
    glm::vec4 inputRotation = glm::vec4 (rotation.x,rotation.y,rotation.z,timeToLive);
    glm::vec4 inputScale = glm::vec4 (scale.x,scale.y,scale.z,gravity);
    ParticleData particleData = ParticleData({0, 0, bilborded, texture}, inputPosition,  inputRotation, inputScale,  velocity, angularVelocity);
    particlesToPush.push_back(particleData);
}

std::vector<glm::vec3> generate_vectors(int n) {
    std::vector<glm::vec3> vectors;
    vectors.reserve(n);
    for (int i = 0; i < n; ++i) {
        float theta = 2.0f*3.14*static_cast<float>(i)/n;
        float x = cos(theta);
        float y = sin(theta);
        vectors.push_back(glm::vec3(x,0,y));
    }
    return vectors;
}

void ParticleEmiter::EmitCircleOfParticles(int timeToLive, int bilborded, int texture, float gravity, glm::vec4 scale, float velocity) {
    std::vector<glm::vec3> velocities = generate_vectors(100);

    for (int i = 0; i < 100; ++i) {
        EmitParticle(timeToLive,bilborded,texture,glm::vec3 (0),gravity,glm::vec4(0),scale, glm::vec4 (velocities[i] * velocity,1),glm::vec4(0));
    }
}

