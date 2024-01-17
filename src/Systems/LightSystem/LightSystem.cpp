//
// Created by redkc on 09/01/2024.
//

#include "LightSystem.h"
#include "glad/glad.h"
#include "imgui.h"

void LightSystem::PushToSSBO() {


    std::vector<DirLightData> dirLightDataArray;
    for (const DirLight light : dirLights) {
        dirLightDataArray.push_back(light.data);
    }

    std::vector<SpotLightData> spotLightDataArray;
    for (const SpotLight& light : spotLights) {
        spotLightDataArray.push_back(light.data);
    }
    
    std::vector<PointLightData> pointLightDataArray;
    for (const PointLight& light : pointLights) {
        pointLightDataArray.push_back(light.data);
    }

    GLuint currentId;
    glGenBuffers(1, &currentId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, currentId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, dirLightDataArray.size() * sizeof(DirLightData), dirLightDataArray.data(),
                 GL_STATIC_DRAW);
    int bindingPoint = 3; // Choose a binding point
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, currentId);

    glGenBuffers(1, &currentId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, currentId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, pointLightDataArray.size() * sizeof(PointLightData), pointLightDataArray.data(),
                 GL_STATIC_DRAW);
    bindingPoint = 4; // Choose a binding point
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, currentId);

    glGenBuffers(1, &currentId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, currentId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, spotLightDataArray.size() * sizeof(SpotLightData), spotLightDataArray.data(),
                 GL_STATIC_DRAW);
    bindingPoint = 5; // Choose a binding point
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, currentId);

    dirLightDataArray.clear();
    pointLightDataArray.clear();
    spotLightDataArray.clear();
}

void LightSystem::showLightTree() {
    if (ImGui::TreeNode("LightSystem")) {
        for (auto &light: lights) {
            light->showImGuiDetails(camera);
        }
        if (ImGui::Button("Push light data to SSBO"))
        {
            PushToSSBO();
        }
        ImGui::TreePop();
    }
}

//Should have done it cleaner don't care enough to do it
void LightSystem::AddDirLight(glm::vec4 direction, glm::vec4 color) {
    dirLights.push_back(DirLight(DirLightData(direction, color)));
    lights.push_back(&dirLights.back());
}

void LightSystem::AddPointLight(glm::vec4 position,
                                float constant,
                                float linear,
                                float quadratic,
                                glm::vec4 color) {
    pointLights.push_back(PointLight(PointLightData(position, constant, linear, quadratic, 0, color)));
    lights.push_back(&pointLights.back());

}

void LightSystem::AddSpotLight(glm::vec4  position,
                               glm::vec4  direction,
                               float cutOff,
                               float outerCutOff,
                               float constant,
                               float linear,
                               float quadratic,
                               glm::vec4 color) {
    spotLights.push_back(SpotLight(SpotLightData(position,direction, cutOff,
             outerCutOff,
             constant,
             linear,
             quadratic,0,0,0,
             color)));
    lights.push_back(&spotLights.back());
}

LightSystem::~LightSystem() {
    dirLights.clear();
    pointLights.clear();
    spotLights.clear();
}

LightSystem::LightSystem(Camera *camera):camera(camera) {

}
