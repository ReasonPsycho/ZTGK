//
// Created by redkc on 10/04/2024.
//

#include "WireRenderer.h"

void WireRenderer::DrawColliders() {
    wireShader.use();
    camera->GetProjectionMatrix();
    glm::mat4 projection = camera->GetProjectionMatrix();
    glm::mat4 view = camera->GetViewMatrix();
    wireShader.setMatrix4("projection", false, glm::value_ptr(projection));
    wireShader.setMatrix4("view", false, glm::value_ptr(view));
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // to draw only lines of polygons
    for (auto &colliderComponent: colliderComponents) {
        colliderComponent->drawWire(&wireShader, primitives);
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void WireRenderer::addComponent(void *component) {
    colliderComponents.push_back(reinterpret_cast<Collider *const>(component));
}

void WireRenderer::removeComponent(void *component) {
    auto component_iter = std::find(colliderComponents.begin(), colliderComponents.end(), reinterpret_cast<Collider *const>(component));

    if (component_iter != colliderComponents.end()) {
        colliderComponents.erase(component_iter);
    }
}

void WireRenderer::showImGuiDetails(Camera *camera) {

}

WireRenderer::WireRenderer(Primitives *primitives, Camera *camera) : primitives(primitives),camera(camera){
    name = "Wire Renderer";

}

void WireRenderer::Innit() {
    wireShader.init();
}

void WireRenderer::DrawRays() {
    wireShader.use();
    camera->GetProjectionMatrix();
    glm::mat4 projection = camera->GetProjectionMatrix();
    glm::mat4 view = camera->GetViewMatrix();
    wireShader.setMatrix4("projection", false, glm::value_ptr(projection));
    wireShader.setMatrix4("view", false, glm::value_ptr(view));

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // to draw only lines of polygons
    for (auto &rayComponent: rayComponents) {
        rayComponent->drawWire(&wireShader);
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
