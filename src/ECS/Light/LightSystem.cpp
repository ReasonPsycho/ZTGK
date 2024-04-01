//
// Created by redkc on 09/01/2024.
//


#include "LightSystem.h"
#include "ECS/Render/RenderSystem.h"

void LightSystem::PushToSSBO() {
    GLenum err;


    GenerateShadowBuffers();

    std::vector<DirLightData> dirLightDataArray;
    for (const DirLight *light: dirLights) {
        dirLightDataArray.push_back(light->data);
    }

    std::vector<SpotLightData> spotLightDataArray;
    for (const SpotLight *light: spotLights) {
        spotLightDataArray.push_back(light->data);
    }

    std::vector<PointLightData> pointLightDataArray;
    for (const PointLight *light: pointLights) {
        pointLightDataArray.push_back(light->data);
    }


    glBindBuffer(GL_SHADER_STORAGE_BUFFER, dirLightBufferId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, dirLightDataArray.size() * sizeof(DirLightData), dirLightDataArray.data(),
                 GL_STREAM_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, dirLightBufferBindingPoint, dirLightBufferId);

    
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, pointLightBufferId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, pointLightDataArray.size() * sizeof(PointLightData),
                 pointLightDataArray.data(),
                 GL_STREAM_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, pointLightBufferBindingPoint, pointLightBufferId);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, spotLightBufferId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, spotLightDataArray.size() * sizeof(SpotLightData), spotLightDataArray.data(),
                 GL_STREAM_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, spotLightBufferBindingPoint, spotLightBufferId);


    if((err = glGetError()) != GL_NO_ERROR) {
        // Log error
        spdlog::error("Some error: {}", err);
    }
    
    dirLightDataArray.clear();
    pointLightDataArray.clear();
    spotLightDataArray.clear();
    isDataPushedToSSBO = true;
}



LightSystem::~LightSystem() {
    dirLights.clear();
    pointLights.clear();
    spotLights.clear();
}

LightSystem::LightSystem(Camera *camera,Scene* scene) : camera(camera),scene(scene) {
name = "Light system";
}

void LightSystem::GenerateShadowBuffers() {
    for (auto &light: lights) {
        light->InnitShadow();
    }
}

void LightSystem::Init() {
    planeDepthShader.init();
    cubeDepthShader.initWithGeometry();

    instancePlaneDepthShader.init();
    instanceCubeDepthShader.initWithGeometry();

    glGenBuffers(1, &dirLightBufferId);
    glGenBuffers(1, &pointLightBufferId);
    glGenBuffers(1, &spotLightBufferId);
    
    PushToSSBO();
}


int TEXTURE_UNITS_OFFSET = 8;
int POINT_SHADOW_OFFSET = TEXTURE_UNITS_OFFSET + 5;

void LightSystem::PushDepthMapsToShader(Shader *shader) { 
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

void LightSystem::Update(double deltaTime) {
    GLenum err;
    int offset = 0;
    RenderSystem* renderSystem = scene->systemManager.getSystem<RenderSystem>();
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, dirLightBufferId);
    for (auto &light: dirLights) {
        if (light->getIsDirty()) {  // Only push it if it's dirty
            light->UpdateData();
            glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset,sizeof(DirLightData), &light->data);
        }
        light->SetUpShadowBuffer(Normal, &planeDepthShader,&instancePlaneDepthShader);
        glClear(GL_DEPTH_BUFFER_BIT);
        renderSystem->SimpleDrawScene(&planeDepthShader);
        offset += sizeof(light->data);
    }

    offset = 0;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, pointLightBufferId);
    for (auto &light: pointLights) {
        if (light->getIsDirty()) {  // Only push it if it's dirty
            light->UpdateData();
            glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, sizeof(PointLightData), &light->data);
            
        }
        light->SetUpShadowBuffer(Normal, &cubeDepthShader,&instanceCubeDepthShader);
        glClear(GL_DEPTH_BUFFER_BIT);
        renderSystem->SimpleDrawScene(&cubeDepthShader);
        offset += sizeof(light->data);
    }

    offset = 0;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, spotLightBufferId);
    for (auto &light: spotLights) {
        if (light->getIsDirty()) {  // Only push it if it's dirty
            light->UpdateData();
            glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset,  sizeof(SpotLightData), &light->data);
        }
        light->SetUpShadowBuffer(Normal, &planeDepthShader,&instancePlaneDepthShader);
        glClear(GL_DEPTH_BUFFER_BIT);
        renderSystem->SimpleDrawScene(&planeDepthShader);
        offset += sizeof(light->data);
    }
     
}

void LightSystem::addComponent(void *component) {
    ILight *light = static_cast<ILight *>(component);
    
    switch (light->lightType) {
        case Point:
            pointLights.push_back(reinterpret_cast<PointLight *>(light));
            if(isDataPushedToSSBO){
                glBufferData(GL_SHADER_STORAGE_BUFFER, pointLights.size() * sizeof(PointLightData), NULL, GL_DYNAMIC_DRAW); // orphaning
                glBufferData(GL_SHADER_STORAGE_BUFFER, pointLights.size() * sizeof(PointLightData), pointLights.data(), GL_DYNAMIC_DRAW);
            }
            break;
        case Directional:
            dirLights.push_back(reinterpret_cast<DirLight *>(light));
            if(isDataPushedToSSBO){
                glBufferData(GL_SHADER_STORAGE_BUFFER, dirLights.size() * sizeof(DirLightData), NULL, GL_DYNAMIC_DRAW); // orphaning
                glBufferData(GL_SHADER_STORAGE_BUFFER, dirLights.size() * sizeof(DirLightData), pointLights.data(), GL_DYNAMIC_DRAW);
            }
            break;
        case Spot:
            spotLights.push_back(reinterpret_cast<SpotLight *>(light));
            if(isDataPushedToSSBO){
                glBufferData(GL_SHADER_STORAGE_BUFFER, spotLights.size() * sizeof(SpotLightData), NULL, GL_DYNAMIC_DRAW); // orphaning
                glBufferData(GL_SHADER_STORAGE_BUFFER, spotLights.size() * sizeof(SpotLightData), spotLights.data(), GL_DYNAMIC_DRAW);
            }
            break;
    }
    lights.push_back(light);
}

void LightSystem::showImGuiDetails(Camera *camera){

}

void LightSystem::removeComponent(void *component) {
    ILight *light = static_cast<ILight *>(component);

    std::vector<PointLight*>::iterator pointLight_iter;
    std::vector<DirLight*>::iterator dirLight_iter;
    std::vector<SpotLight*>::iterator spotLight_iter;



    switch (light->lightType) {
        case Point:
            pointLight_iter = std::find(pointLights.begin(), pointLights.end(), reinterpret_cast<PointLight *const>(component));
            if (pointLight_iter != pointLights.end()) {
                pointLights.erase(pointLight_iter);
            }
            
            if(isDataPushedToSSBO){
                glBufferData(GL_SHADER_STORAGE_BUFFER, pointLights.size() * sizeof(PointLightData), NULL, GL_DYNAMIC_DRAW); // orphaning
                glBufferData(GL_SHADER_STORAGE_BUFFER, pointLights.size() * sizeof(PointLightData), pointLights.data(), GL_DYNAMIC_DRAW);
            }
            break;
        case Directional:
            dirLight_iter = std::find(dirLights.begin(), dirLights.end(), reinterpret_cast<DirLight *const>(component));

            if (dirLight_iter != dirLights.end()) {
                dirLights.erase(dirLight_iter);
            }
            if(isDataPushedToSSBO){
                glBufferData(GL_SHADER_STORAGE_BUFFER, dirLights.size() * sizeof(DirLightData), NULL, GL_DYNAMIC_DRAW); // orphaning
                glBufferData(GL_SHADER_STORAGE_BUFFER, dirLights.size() * sizeof(DirLightData), pointLights.data(), GL_DYNAMIC_DRAW);
            }
            break;
        case Spot:
            spotLight_iter = std::find(spotLights.begin(), spotLights.end(), reinterpret_cast<SpotLight *const>(component));

            if (spotLight_iter != spotLights.end()) {
                spotLights.erase(spotLight_iter);
            }
            if(isDataPushedToSSBO){
                glBufferData(GL_SHADER_STORAGE_BUFFER, spotLights.size() * sizeof(SpotLightData), NULL, GL_DYNAMIC_DRAW); // orphaning
                glBufferData(GL_SHADER_STORAGE_BUFFER, spotLights.size() * sizeof(SpotLightData), spotLights.data(), GL_DYNAMIC_DRAW);
            }
            break;
    }
}
