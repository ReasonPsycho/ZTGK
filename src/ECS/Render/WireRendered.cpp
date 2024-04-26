//
// Created by redkc on 10/04/2024.
//

#include "WireRenderer.h"
#include "ECS/Grid/Tile.h"

void WireRenderer::DrawColliders() {
    
    if(renderBoxes){
        boxShader.use();
        camera->GetProjectionMatrix();
        glm::mat4 projection = camera->GetProjectionMatrix();
        glm::mat4 view = camera->GetViewMatrix();
        boxShader.setMatrix4("projection", false, glm::value_ptr(projection));
        boxShader.setMatrix4("view", false, glm::value_ptr(view));

        glDisable(GL_BLEND);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // to draw only lines of polygons
        PushToSSBO(camera);

        for (unsigned int i = 0; i < boxModel->meshes.size(); i++) {
            glBindVertexArray(boxModel->meshes[i].VAO);
            glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(boxModel->meshes[i].indices.size()),
                                    GL_UNSIGNED_INT, 0, boxColliderDataArray.size());
            glBindVertexArray(0);
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
 
}

void WireRenderer::addComponent(void *component) {
    colliderComponents.push_back(reinterpret_cast<Collider *const>(component));
}

void WireRenderer::removeComponent(void *component) {
    auto component_iter = std::find(colliderComponents.begin(), colliderComponents.end(),
                                    reinterpret_cast<Collider *const>(component));

    if (component_iter != colliderComponents.end()) {
        colliderComponents.erase(component_iter);
    }
}

void WireRenderer::showImGuiDetails(Camera *camera) {
    ImGui::Checkbox("Render boxes",&renderBoxes);
    ImGui::Checkbox("Render rays",&renderRays);
    if(ImGui::Button("Clear rays")){
        rayComponents.clear();
    };
      

}

WireRenderer::WireRenderer(Primitives *primitives, Camera *camera) : primitives(primitives), camera(camera) {
    name = "Wire Renderer";

}

void WireRenderer::Innit() {
    rayShader.init();
    boxShader.init();
    glGenBuffers(1, &wireBoxBufferID);

}

void WireRenderer::DrawRays() {
    if(renderRays){
        rayShader.use();
        camera->GetProjectionMatrix();
        glm::mat4 projection = camera->GetProjectionMatrix();
        glm::mat4 view = camera->GetViewMatrix();
        rayShader.setMatrix4("projection", false, glm::value_ptr(projection));
        rayShader.setMatrix4("view", false, glm::value_ptr(view));

        glDisable(GL_BLEND);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // to draw only lines of polygons
        for (auto &rayComponent: rayComponents) {
            rayComponent->drawWire(&rayShader);
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void WireRenderer::PushToSSBO(Camera *camera) {
    boxColliderDataArray.clear();
    for (auto &collider: colliderComponents) {
        BoxCollider *boxCollider = reinterpret_cast<BoxCollider *>(collider);
        boxColliderDataArray.push_back(boxCollider->boxColliderData);
    }
    
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, wireBoxBufferID);
    glBufferData(GL_SHADER_STORAGE_BUFFER, boxColliderDataArray.size() * sizeof(BoxColliderData),
                 nullptr, //Orphaning buffer
                 GL_STREAM_DRAW);
    glBufferData(GL_SHADER_STORAGE_BUFFER, boxColliderDataArray.size() * sizeof(BoxColliderData),
                 boxColliderDataArray.data(),
                 GL_STREAM_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, wireBoxDataBufferBindingPoint, wireBoxBufferID);

}
