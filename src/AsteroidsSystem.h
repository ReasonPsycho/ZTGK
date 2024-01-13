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
    float maxScale = 2.0f;
    float minScale = 0.5f;
    
    AsteroidsSystem(int size,Shader* asteroidShader);
    void Init();
    void Draw(float deltaTime);
    
    std::vector<AsteroidData> asteroidsData;
    std::vector<std::shared_ptr<Texture>> textures;
    Model asteroidModel = Model(&asteroidModelPath);
    Shader* asteroidShader;
    ComputeShader cumputeShaderMovment = ComputeShader("res/shaders/asteroidMovment.glsl");
    ComputeShader cumputeShaderGridCreation = ComputeShader("res/shaders/asteroidGridCreation.glsl");
    ComputeShader cumputeShaderGridSort = ComputeShader("res/shaders/asteroidGridSort.glsl");
    ComputeShader cumputeShaderGridCalculateOffset = ComputeShader("res/shaders/asteroidGridCalculateOffset.glsl");
    ComputeShader cumputeShaderCollide = ComputeShader("res/shaders/asteroidCollision.glsl");
    ComputeShader cumputeShaderSeperation = ComputeShader("res/shaders/asteroidSeperation.glsl");
private:
    int size;
};


#endif //OPENGLGP_ASTEROIDSSYSTEM_H
