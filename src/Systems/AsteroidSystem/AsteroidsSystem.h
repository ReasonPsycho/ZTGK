//
// Created by redkc on 14/12/2023.
//

#ifndef OPENGLGP_ASTEROIDSSYSTEM_H
#define OPENGLGP_ASTEROIDSSYSTEM_H

#include "glm/vec3.hpp"
#include "glm/trigonometric.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "modelLoading/Shader.h"
#include "modelLoading/ComputeShader.h"
#include "glm/gtc/random.hpp"
#include "modelLoading/Model.h"
#include <random>


struct AsteroidData {
    glm::vec4 position;
    glm::vec4 rotation;
    glm::vec4 scale;
    glm::vec4 velocity;
    glm::vec4 angularVelocity;
    glm::vec4 separationVector;
};

struct CellData {
    int key;
    int cellHash;
};

struct Offsets {
    int value;
};


static string asteroidModelPath = "C:/Users/redkc/CLionProjects/assignment-x-the-project-ReasonPsycho/res/models/asteroid/Asteroid.fbx";


class AsteroidsSystem {
public:
    GLuint ID{};
    float maxScale = 0.5f;
    float minScale = 2.0f;
    glm::mat4x4 planet;
    
    
    AsteroidsSystem(int size,Shader* asteroidShader);
    void Init();
    void Update(float deltaTime);
    void Draw();
    
    std::vector<AsteroidData> asteroidsData;
    std::vector<std::shared_ptr<Texture>> textures;
    Model asteroidModel = Model(&asteroidModelPath);
    Shader* asteroidShader;
    ComputeShader cumputeShaderMovment = ComputeShader("res/shaders/AsteroidSystem/ComputeShaders/asteroidMovment.glsl");
    ComputeShader cumputeShaderGridCreation = ComputeShader("res/shaders/AsteroidSystem/ComputeShaders/asteroidGridCreation.glsl");
    ComputeShader cumputeShaderGridSort = ComputeShader("res/shaders/AsteroidSystem/ComputeShaders/asteroidGridSort.glsl");
    ComputeShader cumputeShaderGridCalculateOffset = ComputeShader("res/shaders/AsteroidSystem/ComputeShaders/asteroidGridCalculateOffset.glsl");
    ComputeShader cumputeShaderCollide = ComputeShader("res/shaders/AsteroidSystem/ComputeShaders/asteroidCollision.glsl");
    ComputeShader cumputeShaderSeperation = ComputeShader("res/shaders/AsteroidSystem/ComputeShaders/asteroidSeperation.glsl");
private:
    int size;
};


#endif //OPENGLGP_ASTEROIDSSYSTEM_H
