//
// Created by redkc on 16/04/2024.
//

#include "ECS/SystemManager.h"
#include "InstanceRenderSystem.h"

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

void InstanceRenderSystem::showImGuiDetails(Camera *camera) {
    ImGui::Checkbox("Update WallData",&updateWallData);
}

void InstanceRenderSystem::DrawTiles(Shader *regularShader,Camera * camera) {
  //it must be here bcs if we mine wall we need to update walls
  //Innit();
  
    PushToSSBO(camera);
    tileModel->meshes[0].material.loadMaterial(regularShader);
    glActiveTexture(GL_TEXTURE0 + tileTextureBindingPoint);
    glBindTexture(GL_TEXTURE_2D_ARRAY, tileTextureArray);
    glUniform1i(glGetUniformLocation(regularShader->ID, "diffuseTextureArray"),tileTextureBindingPoint);
    Grid* grid = systemManager->getSystem<Grid>();
    
    glm::mat4 gridMatrix = glm::translate(glm::mat4(1.0f), (glm::vec3 (grid->Position.x,grid->Position.y,grid->Position.z)));
    regularShader->setMatrix4("gridMatrix", false,glm::value_ptr(gridMatrix));
    
    for (unsigned int i = 0; i < tileModel->meshes.size(); i++) {
        glBindVertexArray(tileModel->meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(tileModel->meshes[i].indices.size()),
                                GL_UNSIGNED_INT, 0, wallData.size());
        glBindVertexArray(0);
    }
}

void InstanceRenderSystem::Update() {
    
}

void InstanceRenderSystem::Innit() {
    glGenTextures(1, &tileTextureArray);
    glBindTexture(GL_TEXTURE_2D_ARRAY, tileTextureArray);
    glTexImage3D(
            GL_TEXTURE_2D_ARRAY,  // target
            0,                    // level, 0 is the base, no mipmap
            GL_RGBA,              // internal format
            512,                  // width
            512,                  // height
            3,                    // depth, the number of layers in the array texture.
            0,                    // border, always 0 in OpenGL ES 
            GL_RGBA,              // format
            GL_UNSIGNED_BYTE,     // type
            NULL                  // data, NULL means to reserve texture data space without loading data.
    );    unsigned char* textureData;
    for(int layer = 0; layer <  numberOfTextures; layer++) {
        int width, height, nrChannels;
        spdlog::info(tilePath + std::to_string(layer) + ".png");
        textureData = LoadTileTexture(tilePath + std::to_string(layer) + ".png", width, height, nrChannels);
        if (textureData) {
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, layer, 512, 512, 1, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
            stbi_image_free(textureData);  // don't forget to free the image memory
        }
    }

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    
    glGenBuffers(1, &wallDataBufferID);
}

InstanceRenderSystem::InstanceRenderSystem() {
    name = "InstanceRenderSystem";
}

void InstanceRenderSystem::PushToSSBO(Camera* camera) {

   Frustum frustum =  createFrustumFromCamera(*camera);
   if(updateWallData){
       wallData.clear();
       Grid* grid = systemManager->getSystem<Grid>();
       for (int x = 0; x < grid->width/10; ++x) {
           for (int z = 0; z < grid->height/10; ++z) {
               Chunk * chunk = &grid->chunkArray[x][z];
               if(chunk->getBoundingVolume().BoundingVolume::isOnFrustum(frustum)){
                   wallData.insert(wallData.end(),grid->chunkArray[x][z].wallDataArray.begin(), grid->chunkArray[x][z].wallDataArray.end()); //This is unsafe but bypasses checks lol
               }
           }
       } 
  

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, wallDataBufferID);
    glBufferData(GL_SHADER_STORAGE_BUFFER, wallData.size() * sizeof(WallData), nullptr, //Orphaning buffer
                 GL_STREAM_DRAW);
    glBufferData(GL_SHADER_STORAGE_BUFFER, wallData.size() * sizeof(WallData), wallData.data(),
                 GL_STREAM_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, wallDataBufferBindingPoint, wallDataBufferID);
   }
   
}

