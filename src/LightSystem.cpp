//
// Created by redkc on 09/01/2024.
//

#include "LightSystem.h"
#include "glad/glad.h"

LightSystem::LightSystem(int size) :size(size){

}

void LightSystem::Init() {
    lights.push_back(Light(glm::vec4(0,0,0,0),glm::vec4(255,255,255,10))); // Fotrh value of color is also intensity
    GLuint currentId;
    glGenBuffers(1, &currentId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, currentId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, lights.size() * sizeof(Light), lights.data(),
                 GL_STATIC_DRAW);
    int bindingPoint = 3; // Choose a binding point
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, currentId);
}
