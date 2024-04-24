//
// Created by redkc on 16/04/2024.
//

#include "InstanceRenderSystem.h"

void InstanceRenderSystem::addComponent(void *component) {
    tileComponents.push_back(reinterpret_cast<Tile *const>(component));

}

void InstanceRenderSystem::removeComponent(void *component) {
    auto component_iter = std::find(tileComponents.begin(), tileComponents.end(), reinterpret_cast<Tile *const>(component));

    if (component_iter != tileComponents.end()) {
        tileComponents.erase(component_iter);
    }
}

void InstanceRenderSystem::showImGuiDetails(Camera *camera) {

}

void InstanceRenderSystem::DrawTiles(Shader *regularShader) {
    Innit();


    for (unsigned int i = 0; i < tileModel->meshes.size(); i++) {
        tileModel->meshes[i].material.loadMaterial(regularShader);
        glBindVertexArray(tileModel->meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(tileModel->meshes[i].indices.size()),
                                GL_UNSIGNED_INT, 0, wallData.size());
        glBindVertexArray(0);
    }
}

void InstanceRenderSystem::Update() {
    
}

void InstanceRenderSystem::Innit() {
    glGenBuffers(1, &wallDataBufferID);

    wallData.clear();
    for (const Tile *tile: tileComponents) {
        for (int i = 0; i < tile->walls.size(); ++i) {
            wallData.push_back(tile->walls[i]);
        }
    }
    
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, wallDataBufferID);
    glBufferData(GL_SHADER_STORAGE_BUFFER, wallData.size() * sizeof(WallData), wallData.data(),
                 GL_STREAM_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, wallDataBufferBindingPoint, wallDataBufferID);
}

InstanceRenderSystem::InstanceRenderSystem() {
    name = "InstanceRenderSystem";
}

