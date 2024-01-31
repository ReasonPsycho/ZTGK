//
// Created by redkc on 09/01/2024.
//

#include "LightSystem.h"
#include "glad/glad.h"
#include "imgui.h"

void LightSystem::PushToSSBO() {


    GenerateShadowBuffers();
    
    std::vector<DirLightData> dirLightDataArray;
    for (const DirLight &light: dirLights) {
        dirLightDataArray.push_back(light.data);
    }

    std::vector<SpotLightData> spotLightDataArray;
    for (const SpotLight &light: spotLights) {
        spotLightDataArray.push_back(light.data);
    }

    std::vector<PointLightData> pointLightDataArray;
    for (const PointLight &light: pointLights) {
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
    glBufferData(GL_SHADER_STORAGE_BUFFER, pointLightDataArray.size() * sizeof(PointLightData),
                 pointLightDataArray.data(),
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
    if (ImGui::TreeNode("Lights")) {
        for (auto &light: lights) {
            light->showImGuiDetails(camera);
        }
        if (ImGui::Button("Push light data to SSBO")) {
            PushToSSBO();
        }
        ImGui::TreePop();
    }
}

//Should have done it cleaner don't care enough to do it
void LightSystem::AddDirLight(glm::vec4 direction, glm::vec4 color) {
    dirLights.push_back(DirLight(&planeDepthShader, &instancePlaneDepthShader, DirLightData(direction, color)));
    lights.push_back(&dirLights.back());
}

void LightSystem::AddPointLight(glm::vec4 position,
                                float constant,
                                float linear,
                                float quadratic,
                                glm::vec4 color) {
    pointLights.push_back(
            PointLight(&cubeDepthShader, &instanceCubeDepthShader,
                       PointLightData(position, constant, linear, quadratic, 0, color)));
    lights.push_back(&pointLights.back());

}

void LightSystem::AddSpotLight(glm::vec4 position,
                               glm::vec4 direction,
                               float cutOff,
                               float outerCutOff,
                               float constant,
                               float linear,
                               float quadratic,
                               glm::vec4 color) {
    spotLights.push_back(
            SpotLight(&planeDepthShader, &instancePlaneDepthShader, SpotLightData(position, direction, cutOff,
                                                                    outerCutOff,
                                                                    constant,
                                                                    linear,
                                                                    quadratic, 0, 0, 0,
                                                                    color)));
    lights.push_back(&spotLights.back());
}

LightSystem::~LightSystem() {
    dirLights.clear();
    pointLights.clear();
    spotLights.clear();
}

LightSystem::LightSystem(Camera *camera) : camera(camera) {

}

void LightSystem::GenerateShadowBuffers() {
    for (auto &light: lights) {
        light->InnitShadow();
    }
}

void LightSystem::GenerateShadows(void (*funcPtr)(), ShaderType shaderType) {
    for (auto &light: lights) {
        light->SetUpShadowBuffer(shaderType);
    }
    glViewport(0, 0, camera->saved_display_w, camera->saved_display_h); // Needed after light generation
}

void LightSystem::Init() {
    planeDepthShader.init();
    cubeDepthShader.init();

    instancePlaneDepthShader.init();
    instanceCubeDepthShader.init();
    PushToSSBO();
}


int TEXTURE_UNITS_OFFSET = 8;
int POINT_SHADOW_OFFSET = TEXTURE_UNITS_OFFSET + 5;

void LightSystem::PushDepthMapsToShader(Shader *shader) { //TODO this should be done throught ILight
    int planeShadowIndex = 0, cubeShadowIndex = 0;
    for (auto &light: lights) {
        if (light->lightType == Point) {
            std::string number = std::to_string(cubeShadowIndex);
            glActiveTexture(GL_TEXTURE0 + TEXTURE_UNITS_OFFSET +
                            cubeShadowIndex); // TEXTURE_UNITS_OFFSET is the number of non-shadow map textures you have
            glBindTexture(GL_TEXTURE_CUBE_MAP, light->depthMap);
            glUniform1i(glGetUniformLocation(shader->ID, ("cubeShadowMaps[" + number + "]").c_str()),
                        TEXTURE_UNITS_OFFSET + cubeShadowIndex);
            cubeShadowIndex++;
        } else {
            std::string number = std::to_string(planeShadowIndex);
            glActiveTexture(GL_TEXTURE0 + POINT_SHADOW_OFFSET +
                            planeShadowIndex); // TEXTURE_UNITS_OFFSET is the number of non-shadow map textures you have
            glBindTexture(GL_TEXTURE_2D, light->depthMap);
            glUniform1i(glGetUniformLocation(shader->ID, ("planeShadowMaps[" + number + "]").c_str()),
                        POINT_SHADOW_OFFSET + planeShadowIndex);
            planeShadowIndex++;
        }
    
    }
}
