//
// Created by redkc on 09/01/2024.
//


#include "LightSystem.h"
#include "ECS/Render/RenderSystem.h"
#include "ECS/Render/InstanceRenderSystem.h"

void LightSystem::PushToSSBO() {


    
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

    GLenum err = glGetError();

    
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, dirLightBufferId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, maxDirLight * sizeof(DirLightData),NULL,
                 GL_DYNAMIC_DRAW);
    glBufferData(GL_SHADER_STORAGE_BUFFER, maxDirLight * sizeof(DirLightData), dirLightDataArray.data(),
                 GL_DYNAMIC_DRAW);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, dirLightBufferBindingPoint, dirLightBufferId);
    err = glGetError();


    glBindBuffer(GL_SHADER_STORAGE_BUFFER, pointLightBufferId);

    glBufferData(GL_SHADER_STORAGE_BUFFER, maxPointLight * sizeof(PointLightData),
                 NULL,
                 GL_DYNAMIC_DRAW);
    glBufferData(GL_SHADER_STORAGE_BUFFER, maxPointLight * sizeof(PointLightData),
                 pointLightDataArray.data(),
                 GL_DYNAMIC_DRAW);

    
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, pointLightBufferBindingPoint, pointLightBufferId);

    
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, spotLightBufferId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, maxSpotLight * sizeof(SpotLightData), NULL,
                 GL_DYNAMIC_DRAW);
    glBufferData(GL_SHADER_STORAGE_BUFFER, maxSpotLight * sizeof(SpotLightData), spotLightDataArray.data(),
                 GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, spotLightBufferBindingPoint, spotLightBufferId);
    
    dirLightDataArray.clear();
    pointLightDataArray.clear();
    spotLightDataArray.clear();
}


LightSystem::~LightSystem() {
    dirLights.clear();
    pointLights.clear();
    spotLights.clear();
    delete[] whiteImage;
}

LightSystem::LightSystem(Camera *camera, Scene *scene) : camera(camera), scene(scene) {
    name = "Light system";
}

void LightSystem::GenerateShadowBuffers() {
    int index = 0;
    for (auto &light: dirLights) {
        light->Innit(SHADOW_WIDTH, SHADOW_HEIGHT, index++);
    }

    for (auto &light: spotLights) {
        light->Innit(SHADOW_WIDTH, SHADOW_HEIGHT, index++);

    }

    index = 0;
    for (auto &light: pointLights) {
        light->Innit(SHADOW_WIDTH, SHADOW_HEIGHT, index++);
    }
}

void LightSystem::Init() {
    glGenFramebuffers(1, &depthFBO);

    for (int i = 0; i < SHADOW_WIDTH * SHADOW_HEIGHT * 3; i += 3) {
        whiteImage[i] = whitePixel[0];
        whiteImage[i + 1] = whitePixel[1];
        whiteImage[i + 2] = whitePixel[2];
    }
    
    planeDepthShader.init();
    cubeDepthShader.init();

    instancePlaneDepthShader.init();
    instanceCubeDepthShader.init();
    
    createPlaneShadowMap();
    createCubeShadowMap();

    glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, 0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    glGenBuffers(1, &dirLightBufferId);
    glGenBuffers(1, &pointLightBufferId);
    glGenBuffers(1, &spotLightBufferId);
    
    GenerateShadowBuffers();
}


void LightSystem::PushDepthMapsToShader(Shader *shader) {
    shader->use();
    glActiveTexture(GL_TEXTURE0 + PLANE_SHADOW_TEXTURE_INDEX);
    glBindTexture(GL_TEXTURE_2D_ARRAY, planeShadowMaps);
    glUniform1i(glGetUniformLocation(shader->ID, "planeShadowMaps"), PLANE_SHADOW_TEXTURE_INDEX);

    glActiveTexture(GL_TEXTURE0 + CUBE_SHADOW_INDEX);
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, cubeShadowMaps);
    glUniform1i(glGetUniformLocation(shader->ID, "cubeShadowMaps"), CUBE_SHADOW_INDEX);

    shader->setInt("spotLightAmount", spotLights.size());
    shader->setInt("dirLightAmount", dirLights.size());
    shader->setInt("pointLightAmount", pointLights.size());
}

void LightSystem::UpdateImpl() {

    for (auto &light: lights) {
        if (light->getIsDirty() && light->isActive) {  // Only push it if it's dirty
            light->UpdateData(SHADOW_HEIGHT, SHADOW_WIDTH);
        }
    }

    PushToSSBO();

    RenderCubeDepthMap();
    RenderCubeDepthMapInstanced();
    RenderPlaneDepthMap();
    RenderPlaneDepthMapInstanced();
}

void LightSystem::addComponent(void *component) {
    ILight *light = static_cast<ILight *>(component);
    ZoneScopedN("Add Light");

    switch (light->lightType) {
        case Point:
            pointLights.push_back(reinterpret_cast<PointLight *>(light));
            break;
        case Directional:
            dirLights.push_back(reinterpret_cast<DirLight *>(light));
            break;
        case Spot:
            spotLights.push_back(reinterpret_cast<SpotLight *>(light));
            break;
    }
    
    lights.push_back(light);
}

void LightSystem::showImGuiDetailsImpl(Camera *camera) {
    ImGui::ColorEdit4("Diffuse", glm::value_ptr(gloabalPointLightData.diffuse));
    ImGui::ColorEdit4("Specular", glm::value_ptr(gloabalPointLightData.specular));
    ImGui::InputFloat("Constant", &gloabalPointLightData.constant);
    ImGui::InputFloat("Linear", &gloabalPointLightData.linear);
    ImGui::InputFloat("Quadratic", &gloabalPointLightData.quadratic);
    if (ImGui::Button("Update lights globally")){
        for (auto pointLight: pointLights) {
            pointLight->data = gloabalPointLightData;
            pointLight->setIsDirty(true);
        }
    }
}

void LightSystem::removeComponent(void *component) {
    ILight *light = static_cast<ILight *>(component);

    std::vector<PointLight *>::iterator pointLight_iter;
    std::vector<DirLight *>::iterator dirLight_iter;
    std::vector<SpotLight *>::iterator spotLight_iter;


    switch (light->lightType) {
        case Point:
            pointLight_iter = std::find(pointLights.begin(), pointLights.end(),
                                        reinterpret_cast<PointLight *const>(component));
            if (pointLight_iter != pointLights.end()) {
                pointLights.erase(pointLight_iter);
            }
            break;
        case Directional:
            dirLight_iter = std::find(dirLights.begin(), dirLights.end(), reinterpret_cast<DirLight *const>(component));

            if (dirLight_iter != dirLights.end()) {
                dirLights.erase(dirLight_iter);
            }
            break;
        case Spot:
            spotLight_iter = std::find(spotLights.begin(), spotLights.end(),
                                       reinterpret_cast<SpotLight *const>(component));
            if (spotLight_iter != spotLights.end()) {
                spotLights.erase(spotLight_iter);
            }
            break;
    }
    
    auto light_iter = std::find(lights.begin(), lights.end(),reinterpret_cast<ILight *const>(component));
    if (light_iter != lights.end()) {
        lights.erase(light_iter);
    }
}

void LightSystem::createPlaneShadowMap() {
    

    glGenTextures(1, &planeShadowMaps);

    glBindTexture(GL_TEXTURE_2D_ARRAY, planeShadowMaps);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT,maxDirLight + maxSpotLight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    for (GLsizei layer = 0; layer < maxDirLight + maxSpotLight; layer++) {
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, layer, SHADOW_WIDTH, SHADOW_HEIGHT, 1, GL_RGB, GL_UNSIGNED_BYTE,whiteImage);
    }


    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);


}

void LightSystem::createCubeShadowMap() {


    glGenTextures(1, &cubeShadowMaps);
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, cubeShadowMaps);
    glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, maxPointLight * 6,
                 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    for (unsigned int light = 0; light < maxPointLight; ++light) {
        for (unsigned int face = 0; face < 6; ++face) {
            //Here (your_loaded_image) refers your image data loaded using any image loading libraries.
            glTexSubImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 0, 0, 0, light * 6 + face, SHADOW_WIDTH, SHADOW_HEIGHT, 1,
                            GL_RGB, GL_UNSIGNED_BYTE, whiteImage);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);;
    
}

void LightSystem::RenderPlaneDepthMapInstanced() {

    int index = 0;
    InstanceRenderSystem *instanceRenderSystem = scene->systemManager.getSystem<InstanceRenderSystem>();
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, dirLightBufferId);
    for (auto &light: dirLights) {
        ZoneScopedN("DirLight");
        if(light->isActive) {

            light->SetUpShadowBuffer(&instancePlaneDepthShader,
                                     planeShadowMaps, index, 0);
            instancePlaneDepthShader.use();
            instanceRenderSystem->SimpleDrawTiles(&instancePlaneDepthShader, camera, light->data.position, 100);
        }
        index++;
    }

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, spotLightBufferId);
    for (auto &light: spotLights) {
        ZoneScopedN("SpotLight");
        if(light->isActive) {

            light->SetUpShadowBuffer(&instancePlaneDepthShader,
                                     planeShadowMaps, index, 0);
            instancePlaneDepthShader.use();
            instanceRenderSystem->SimpleDrawTiles(&instancePlaneDepthShader, camera, light->data.position, light->data.position[3]);
        }
        index++;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_BACK);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void LightSystem::RenderPlaneDepthMap() {
    GLenum err;
    int index = 0;
    RenderSystem *renderSystem = scene->systemManager.getSystem<RenderSystem>();
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, dirLightBufferId);
    for (auto &light: dirLights) {
        ZoneScopedN("DirLight");
        if(light->isActive) {
            light->SetUpShadowBuffer(&planeDepthShader,
                                     planeShadowMaps,index , 0);
            planeDepthShader.use();
            renderSystem->SimpleDrawScene(&planeDepthShader, light->data.position, 100);
        }
        index++;
    }

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, spotLightBufferId);
    for (auto &light: spotLights) {
        ZoneScopedN("SpotLight");
        if(light->isActive) {

            light->SetUpShadowBuffer(&planeDepthShader,
                                     planeShadowMaps, index, 0);
            planeDepthShader.use();
            renderSystem->SimpleDrawScene(&planeDepthShader, light->data.position, light->data.position[3]);
        }
        index++;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_BACK);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void LightSystem::RenderCubeDepthMapInstanced() {
    GLenum err;
    int index = 0;
    InstanceRenderSystem *instanceRenderSystem = scene->systemManager.getSystem<InstanceRenderSystem>();
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

    index = 0;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, pointLightBufferId);
    for (auto &light: pointLights) {
        ZoneScopedN("PointLight");
        for (int i = 0; i < 6; i++) {
            if (light->isActive) {

                light->SetUpShadowBuffer(&instanceCubeDepthShader,
                                         cubeShadowMaps, index, i);
                instanceCubeDepthShader.use();
                instanceRenderSystem->SimpleDrawTiles(&instanceCubeDepthShader, camera, light->data.position, light->data.position[3]);
            }
        }
        index++;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_BACK);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void LightSystem::RenderCubeDepthMap() {
    GLenum err;
    int index = 0;
    RenderSystem *renderSystem = scene->systemManager.getSystem<RenderSystem>();
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);

    index = 0;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, pointLightBufferId);
    for (auto &light: pointLights) {
        ZoneScopedN("PointLight");
        if(light->isActive) {
            for (int i = 0; i < 6; i++) {

                light->SetUpShadowBuffer(&cubeDepthShader,
                                         cubeShadowMaps, index, i);
                cubeDepthShader.use();
                renderSystem->SimpleDrawScene(&cubeDepthShader, light->data.position, light->data.position[3]);
            }
        }
        index++;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_BACK);
    glClear(GL_DEPTH_BUFFER_BIT);
}
