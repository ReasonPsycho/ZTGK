//
// Created by redkc on 16/04/2024.
//

#include "ECS/SystemManager.h"
#include "InstanceRenderSystem.h"
#include <filesystem>

unsigned char* LoadTileTexture(const std::string& file_name, int& width, int& height, int& nrChannels)
{
    unsigned char *data = stbi_load(file_name.c_str(), &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cout << "Failed to load tile texture: " << file_name << std::endl;
    }else{
        std::cout << "Loaded texture: " << file_name << ", width: " << width << ", height: " << height << ", nrChannels: " << nrChannels << std::endl;
    }
    return data;
}

void InstanceRenderSystem::addComponent(void *component) {

}

void InstanceRenderSystem::removeComponent(void *component) {

}

void InstanceRenderSystem::showImGuiDetailsImpl(Camera *camera) {
    ImGui::Text("Wall amount %d",wallData.size());
    double step = 0.0001f;
    ImGui::InputScalar("Max bias",ImGuiDataType_Double, &maxBias, &step);
    ImGui::InputScalar("biasMuliplayer",ImGuiDataType_Double, &biasMuliplayer, &step);
    ImGui::InputScalar("factor",ImGuiDataType_Double, &factor, &step);
    ImGui::InputScalar("units",ImGuiDataType_Double, &units, &step);
    ImGui::SliderFloat("Dirt layer",&dirtLayer,0,1);
}

void InstanceRenderSystem::DrawTiles(Shader *regularShader,Camera * camera) {
  //it must be here bcs if we mine wall we need to UpdateImpl walls
  //Innit();
    ZoneScopedN("Draw tiles");
    regularShader->use();
    wallMaterial.loadInstancedMaterial(regularShader);
    Grid* grid = systemManager->getSystem<Grid>();
    glm::mat4 gridMatrix = glm::translate(glm::mat4(1.0f), (glm::vec3 (grid->Position.x,grid->Position.y,grid->Position.z)));
    regularShader->setMatrix4("gridMatrix", false,glm::value_ptr(gridMatrix));
    regularShader->setFloat("biasMuliplayer", biasMuliplayer);
    regularShader->setFloat("heightScale", 0.03);
    regularShader->setFloat("dirtLevel",dirtLayer);
    
    for (unsigned int i = 0; i < tileModel->meshes.size(); i++) {
        glBindVertexArray(tileModel->meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(tileModel->meshes[i].indices.size()),
                                GL_UNSIGNED_INT, 0, wallData.size());
        glBindVertexArray(0);
    }
}


void InstanceRenderSystem::SimpleDrawTiles(Shader *regularShader, Camera *camera) {
    ZoneScopedN("Simple draw tiles");
    glPolygonOffset(factor, units); // You can experiment with these values
    glEnable(GL_POLYGON_OFFSET_FILL);
    regularShader->use();
    Grid* grid = systemManager->getSystem<Grid>();

    glm::mat4 gridMatrix = glm::translate(glm::mat4(1.0f), (glm::vec3 (grid->Position.x,grid->Position.y,grid->Position.z)));
    regularShader->setMatrix4("gridMatrix", false,glm::value_ptr(gridMatrix));
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
    Frustum frustum =  createFrustumFromCamera(*camera);
    wallData.clear();
    Grid* grid = systemManager->getSystem<Grid>();
    for (int x = 0; x < grid->width/grid->chunkWidth; ++x) {
        for (int z = 0; z < grid->height/grid->chunkHeight; ++z) {
            Chunk * chunk = grid->chunkArray[x][z];
            if(chunk->getBoundingVolume().BoundingVolume::isOnFrustum(frustum)){
                chunk->isVisible = true;
                for (auto &wallDataPtr : grid->chunkArray[x][z]->wallDataArray) {
                    wallData.push_back(*wallDataPtr);
                }
            }else{
                chunk->isVisible = false;
            }
        }
    }
}

void InstanceRenderSystem::Innit() {
    glGenBuffers(1, &wallDataBufferID);
    std::filesystem::path diffuseTexturesDictionary("res/textures/tiles/Diffuse"); // Replace with your directory
    if (std::filesystem::exists(diffuseTexturesDictionary) && std::filesystem::is_directory(diffuseTexturesDictionary)) {
        for (const auto& entry : std::filesystem::directory_iterator(diffuseTexturesDictionary)) {
            if (entry.is_regular_file() && entry.path().extension() == ".png") {
                std::cout << "PNG file located: " << entry.path().string() << std::endl;
                wallMaterial.diffuseTextures.push_back(std::make_shared<Texture>(entry.path().string(),""));
            }
        }
    }

    std::filesystem::path specularTexturesDictionary("res/textures/tiles/Specular"); // Replace with your directory
    if (std::filesystem::exists(specularTexturesDictionary) && std::filesystem::is_directory(specularTexturesDictionary)) {
        for (const auto& entry : std::filesystem::directory_iterator(specularTexturesDictionary)) {
            if (entry.is_regular_file() && entry.path().extension() == ".png") {
                std::cout << "PNG file located: " << entry.path().string() << std::endl;
                wallMaterial.specularTextures.push_back(std::make_shared<Texture>(entry.path().string(),""));
            }
        }
    }

    std::filesystem::path normalTexturesDictionary("res/textures/tiles/Normal"); // Replace with your directory
    if (std::filesystem::exists(normalTexturesDictionary) && std::filesystem::is_directory(normalTexturesDictionary)) {
        for (const auto& entry : std::filesystem::directory_iterator(normalTexturesDictionary)) {
            if (entry.is_regular_file() && entry.path().extension() == ".png") {
                std::cout << "PNG file located: " << entry.path().string() << std::endl;
                wallMaterial.normalTextures.push_back(std::make_shared<Texture>(entry.path().string(),""));
            }
        }
    } 
    std::filesystem::path depthTexturesDictionary("res/textures/tiles/Depth"); // Replace with your directory
    if (std::filesystem::exists(depthTexturesDictionary) && std::filesystem::is_directory(depthTexturesDictionary)) {
        for (const auto& entry : std::filesystem::directory_iterator(depthTexturesDictionary)) {
            if (entry.is_regular_file() && entry.path().extension() == ".png") {
                std::cout << "PNG file located: " << entry.path().string() << std::endl;
                wallMaterial.depthTextures.push_back(std::make_shared<Texture>(entry.path().string(),""));
            }
        }
    }

    wallMaterial.mapTextureArrays();
}

InstanceRenderSystem::InstanceRenderSystem(Camera * camera): camera(camera) {
    name = "InstanceRenderSystem";
}

void InstanceRenderSystem::PushToSSBO(Camera* camera) {
    
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, wallDataBufferID);
    glBufferData(GL_SHADER_STORAGE_BUFFER, wallData.size() * sizeof(WallData), nullptr, //Orphaning buffer
                 GL_STREAM_DRAW);
    glBufferData(GL_SHADER_STORAGE_BUFFER, wallData.size() * sizeof(WallData), wallData.data(),
                 GL_STREAM_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, wallDataBufferBindingPoint, wallDataBufferID);
   
   
}

