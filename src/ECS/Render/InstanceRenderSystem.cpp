//
// Created by redkc on 16/04/2024.
//

#include "ECS/Render/ParticleSystem.h"
#include "ECS/SystemManager.h"
#include "ECS/Render/Pipelines/Phong/PhongPipeline.h"
#include "InstanceRenderSystem.h"
#include <filesystem>

unsigned char *LoadTileTexture(const std::string &file_name, int &width, int &height, int &nrChannels) {
    unsigned char *data = stbi_load(file_name.c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        std::cout << "Failed to load tile texture: " << file_name << std::endl;
    } else {
        std::cout << "Loaded texture: " << file_name << ", width: " << width << ", height: " << height << ", nrChannels: " << nrChannels << std::endl;
    }
    return data;
}

void InstanceRenderSystem::addComponent(void *component) {
}

void InstanceRenderSystem::removeComponent(void *component) {

}

void InstanceRenderSystem::showImGuiDetailsImpl(Camera *camera) {

    ImGui::SliderFloat("Left", &left, -2000.0f, 2000.0f);
    ImGui::SliderFloat("Right", &right, -2000.0f, 2000.0f);
    ImGui::SliderFloat("Bottom", &bottom, -2000.0f, 2000.0f);
    ImGui::SliderFloat("Top", &top, -2000.0f, 2000.0f);
    ImGui::SliderFloat("Near", &near, 0.0f, 500.0f);
    ImGui::SliderFloat("Far", &far, 0.0f, 500.0f);

// Displaying the Camera Matrix
    ImGui::Text("Camera Matrix");
    ImGui::InputFloat3("Camera Position", &cameraPos[0]);
    ImGui::InputFloat3("Camera Target", &cameraTarget[0]);
    ImGui::InputFloat3("Up Vector", &upVector[0]);
    
    ImGui::Text("Variable value: %zu", loadedChunks.size());
}

void InstanceRenderSystem::DrawTiles(Shader *regularShader, Camera *camera) {
    //it must be here bcs if we mine wall we need to UpdateImpl walls
    //Innit();
    ZoneScopedN("Draw tiles");

    wallData.clear();

    for (auto chunk: loadedChunks) {
        for (auto &wallDataPtr: chunk->wallDataArray) {
            wallData.push_back(*wallDataPtr);
        }
    }

    PushToSSBO();

    regularShader->use();
    wallMaterial.loadInstancedMaterial(regularShader);
    Grid *grid = systemManager->getSystem<Grid>();
    glm::mat4 gridMatrix = glm::translate(glm::mat4(1.0f), (glm::vec3(grid->Position.x, grid->Position.y, grid->Position.z)));
    regularShader->setMatrix4("gridMatrix", false, glm::value_ptr(gridMatrix));
    regularShader->setFloat("biasMuliplayer", biasMuliplayer);
    regularShader->setFloat("heightScale", 0.03);

    for (unsigned int i = 0; i < tileModel->meshes.size(); i++) {
        glBindVertexArray(tileModel->meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(tileModel->meshes[i].indices.size()),
                                GL_UNSIGNED_INT, 0, wallData.size());
        glBindVertexArray(0);
    }

}


void InstanceRenderSystem::SimpleDrawTiles(Shader *regularShader, Camera *camera, glm::vec3 viewPos, float renderDistance) {
    ZoneScopedN("Simple draw tiles");

    wallData.clear();   

    for (auto chunk: loadedChunks) {
        if (glm::distance(chunk->getEntity()->transform.getGlobalPosition(), viewPos) < renderDistance) {
            for (auto &wallDataPtr: chunk->wallDataArray) {
                wallData.push_back(*wallDataPtr);
            }
        }
    }

    PushToSSBO();

    glPolygonOffset(factor, units); // You can experiment with these values
    glEnable(GL_POLYGON_OFFSET_FILL);
    regularShader->use();
    Grid *grid = systemManager->getSystem<Grid>();

    glm::mat4 gridMatrix = glm::translate(glm::mat4(1.0f), (glm::vec3(grid->Position.x, grid->Position.y, grid->Position.z)));
    regularShader->setMatrix4("gridMatrix", false, glm::value_ptr(gridMatrix));
    regularShader->setFloat("maxBias", maxBias);
    regularShader->setFloat("biasMuliplayer", biasMuliplayer);


    for (unsigned int i = 0; i < tileModel->meshes.size(); i++) {
        glBindVertexArray(tileModel->meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(tileModel->meshes[i].indices.size()),
                                GL_UNSIGNED_INT, 0, wallData.size());
        glBindVertexArray(0);
    }

    glDisable(GL_POLYGON_OFFSET_FILL);
}


void InstanceRenderSystem::UpdateImpl() {
    Frustum frustum = createFrustumFromCamera(*camera);
    loadedChunks.clear();
    Grid *grid = systemManager->getSystem<Grid>();
    for (int x = 0; x < grid->width / grid->chunkWidth; ++x) {
        for (int z = 0; z < grid->height / grid->chunkHeight; ++z) {
            Chunk *chunk = grid->chunkArray[x][z];
            if (chunk->getBoundingVolume().BoundingVolume::isOnFrustum(frustum)) {
                chunk->isVisible = true;
                if(chunk->localLight != nullptr){
                    chunk->localLight->isActive = true;
                }
                loadedChunks.push_back(chunk);
            } else {
                chunk->isVisible = false;
                if(chunk->localLight != nullptr){
                    chunk->localLight->isActive = false;
                }
            }
        }
    }
}

void InstanceRenderSystem::Innit() {

    //Buffers
    glGenBuffers(1, &wallDataBufferID);

    //Wall material
    std::filesystem::path diffuseTexturesDictionary("res/textures/tiles/Diffuse"); // Replace with your directory
    if (std::filesystem::exists(diffuseTexturesDictionary) && std::filesystem::is_directory(diffuseTexturesDictionary)) {
        for (const auto &entry: std::filesystem::directory_iterator(diffuseTexturesDictionary)) {
            if (entry.is_regular_file() && entry.path().extension() == ".png") {
                std::cout << "PNG file located: " << entry.path().string() << std::endl;
                wallMaterial.diffuseTextures.push_back(std::make_shared<Texture>(entry.path().string(), ""));
            }
        }
    }

    std::filesystem::path specularTexturesDictionary("res/textures/tiles/Specular"); // Replace with your directory
    if (std::filesystem::exists(specularTexturesDictionary) && std::filesystem::is_directory(specularTexturesDictionary)) {
        for (const auto &entry: std::filesystem::directory_iterator(specularTexturesDictionary)) {
            if (entry.is_regular_file() && entry.path().extension() == ".png") {
                std::cout << "PNG file located: " << entry.path().string() << std::endl;
                wallMaterial.specularTextures.push_back(std::make_shared<Texture>(entry.path().string(), ""));
            }
        }
    }

    std::filesystem::path normalTexturesDictionary("res/textures/tiles/Normal"); // Replace with your directory
    if (std::filesystem::exists(normalTexturesDictionary) && std::filesystem::is_directory(normalTexturesDictionary)) {
        for (const auto &entry: std::filesystem::directory_iterator(normalTexturesDictionary)) {
            if (entry.is_regular_file() && entry.path().extension() == ".png") {
                std::cout << "PNG file located: " << entry.path().string() << std::endl;
                wallMaterial.normalTextures.push_back(std::make_shared<Texture>(entry.path().string(), ""));
            }
        }
    }
    std::filesystem::path depthTexturesDictionary("res/textures/tiles/Depth"); // Replace with your directory
    if (std::filesystem::exists(depthTexturesDictionary) && std::filesystem::is_directory(depthTexturesDictionary)) {
        for (const auto &entry: std::filesystem::directory_iterator(depthTexturesDictionary)) {
            if (entry.is_regular_file() && entry.path().extension() == ".png") {
                std::cout << "PNG file located: " << entry.path().string() << std::endl;
                wallMaterial.depthTextures.push_back(std::make_shared<Texture>(entry.path().string(), ""));
            }
        }
    }
    

    wallMaterial.mapTextureArrays();

    //Light material

    lightMaterial.depthTextures.push_back(std::make_shared<Texture>("res/textures/lights/Depth/DepthMap.png", ""));
    lightMaterial.diffuseTextures.push_back(std::make_shared<Texture>("res/textures/lights/Diffuse/bubble2.png", ""));
    lightMaterial.normalTextures.push_back(std::make_shared<Texture>("res/textures/lights/Normal/NormalMap.png", ""));
    lightMaterial.specularTextures.push_back(std::make_shared<Texture>("res/textures/lights/Specular/bubble2.png", ""));


    std::filesystem::path particleDiffuseTexturesDictionary("res/textures/particles"); // Replace with your directory
    if (std::filesystem::exists(particleDiffuseTexturesDictionary) && std::filesystem::is_directory(particleDiffuseTexturesDictionary)) {
        for (const auto &entry: std::filesystem::directory_iterator(particleDiffuseTexturesDictionary)) {
            if (entry.is_regular_file() && entry.path().extension() == ".png") {
                std::cout << "PNG file located: " << entry.path().string() << std::endl;
                particleMaterial.depthTextures.push_back(std::make_shared<Texture>(entry.path().string(), ""));
                particleMaterial.diffuseTextures.push_back(std::make_shared<Texture>(entry.path().string(), ""));
                particleMaterial.normalTextures.push_back(std::make_shared<Texture>(entry.path().string(), ""));
                particleMaterial.specularTextures.push_back(std::make_shared<Texture>(entry.path().string(), ""));
            }
        }
    }

    particleMaterial.mapTextureArrays();

    glGenTextures(1, &minimap);

//Specify your desired texture dimensions
    int width = 400;
    int height = 400;

// Bind the texture object and specify its parameters
    glBindTexture(GL_TEXTURE_2D, minimap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenFramebuffers(1, &minimapFbo);

// Bind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, minimapFbo);

// Attach the texture to the framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, minimap, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

InstanceRenderSystem::InstanceRenderSystem(Camera *camera) : camera(camera) {
    name = "InstanceRenderSystem";
}

void InstanceRenderSystem::PushToSSBO() {
    ZoneScopedN("InstanceRenderSystem - PushToSSBO");

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, wallDataBufferID);
    glBufferData(GL_SHADER_STORAGE_BUFFER, wallData.size() * sizeof(WallData), nullptr, //Orphaning buffer
                 GL_STREAM_DRAW);
    glBufferData(GL_SHADER_STORAGE_BUFFER, wallData.size() * sizeof(WallData), wallData.data(),
                 GL_STREAM_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, wallDataBufferBindingPoint, wallDataBufferID);


}

void InstanceRenderSystem::DrawLights(Shader *regularShader, Camera *camera) {
    ZoneScopedN("Simple draw tiles");
    LightSystem *lightSystem = systemManager->getSystem<LightSystem>();
    PhongPipeline *phongPipline = systemManager->getSystem<PhongPipeline>();
    glEnable(GL_BLEND);
    glDisablei(GL_BLEND, phongPipline->colorAttachments[2]);
    regularShader->use();
    lightMaterial.loadMaterial(regularShader);
    regularShader->setInt("spotLightAmount", lightSystem->spotLights.size());
    regularShader->setInt("dirLightAmount", lightSystem->dirLights.size());
    regularShader->setInt("pointLightAmount", lightSystem->pointLights.size());
    int lightAmount = lightSystem->spotLights.size() + lightSystem->dirLights.size() + lightSystem->pointLights.size();
    for (unsigned int i = 0; i < tileModel->meshes.size(); i++) {
        glBindVertexArray(tileModel->meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(tileModel->meshes[i].indices.size()),
                                GL_UNSIGNED_INT, 0, lightAmount);
        glBindVertexArray(0);
    }
    glDisable(GL_BLEND);
}

void InstanceRenderSystem::DrawParticles(Shader *regularShader, Camera *camera) {
//it must be here bcs if we mine wall we need to UpdateImpl walls
    //Innit();
    ZoneScopedN("Draw Particle");
    regularShader->use();
    particleMaterial.loadInstancedMaterial(regularShader);
    for (unsigned int i = 0; i < tileModel->meshes.size(); i++) {
        glBindVertexArray(tileModel->meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(tileModel->meshes[i].indices.size()),
                                GL_UNSIGNED_INT, 0, systemManager->getSystem<ParticleSystem>()->particlesData.size());
        glBindVertexArray(0);
    }
}

void InstanceRenderSystem::DrawMinimap(Shader *regularShader) {
//it must be here bcs if we mine wall we need to UpdateImpl walls
    //Innit();
    ZoneScopedN("Draw tiles");

    glBindFramebuffer(GL_FRAMEBUFFER, minimapFbo);

    wallData.clear();
    Grid *grid = systemManager->getSystem<Grid>();

    for (int x = 0; x < grid->width / grid->chunkWidth; ++x) {
        for (int z = 0; z < grid->height / grid->chunkHeight; ++z) {
            Chunk *chunk = grid->chunkArray[x][z];
            for (auto &wallDataPtr: chunk->wallDataArray) {
                wallData.push_back(*wallDataPtr);
            }
        }
    }
    PushToSSBO();

    glm::mat4 projection = glm::ortho(left, right, bottom, top, near, far);

    glm::mat4 view = glm::lookAt(
            cameraPos,  // Camera position
            cameraTarget,  // Look towards this point
            upVector  // Head is up
    );
    
    regularShader->use();
    regularShader->setMatrix4("projection", false, glm::value_ptr(projection));
    regularShader->setMatrix4("view", false, glm::value_ptr(view));
    regularShader->setVec3("camPos", cameraPos.x, cameraPos.y, cameraPos.z);

    for (unsigned int i = 0; i < tileModel->meshes.size(); i++) {
        glBindVertexArray(tileModel->meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(tileModel->meshes[i].indices.size()),
                                GL_UNSIGNED_INT, 0, wallData.size());
        glBindVertexArray(0);
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
