//
// Created by redkc on 09/01/2024.
//

#include "LightSystem.h"
#include "glad/glad.h"

LightSystem::LightSystem()= default;

void LightSystem::Init() {
    dirLights.push_back(DirLight(glm::vec4(-0.2f, -1.0f, -0.3f,0),glm::vec4(255,255,255,0.5f))); // Fotrh value of color is also intensity
    pointLights.push_back(PointLight(glm::vec4(0, 0, 0,0), 1.0f, 0.09f, 0.032f,0.0f,glm::vec4(255,255,255,1))); // Fotrh value of color is also intensity
    spotLights.push_back(SpotLight(glm::vec4(0, 0, 20.0f,0),glm::vec4(0, 0, -1.0f,0),12.5f,15.0f, 1.0f, 0.09f, 0.032f,0,0,0,glm::vec4(255,255,255,1))); // Fotrh value of color is also intensity
 
    GLuint currentId;
    glGenBuffers(1, &currentId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, currentId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, dirLights.size() * sizeof(DirLight), dirLights.data(),
                 GL_STATIC_DRAW);
    int bindingPoint = 3; // Choose a binding point
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, currentId);

    glGenBuffers(1, &currentId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, currentId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, pointLights.size() * sizeof(PointLight), pointLights.data(),
                 GL_STATIC_DRAW);
    bindingPoint = 4; // Choose a binding point
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, currentId);

    glGenBuffers(1, &currentId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, currentId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, spotLights.size() * sizeof(SpotLight), spotLights.data(),
                 GL_STATIC_DRAW);
    bindingPoint = 5; // Choose a binding point
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, currentId);
}
