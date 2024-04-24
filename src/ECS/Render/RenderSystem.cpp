//
// Created by redkc on 25/02/2024.
//

#include "RenderSystem.h"


void RenderSystem::DrawScene(Shader *regularShader, Camera *camera) {
    Frustum frustum = createFrustumFromCamera(*camera);
    for (auto &renderComponent: renderComponents) {
        renderComponent->draw(*regularShader,&frustum);
    }
}

void RenderSystem::SimpleDrawScene(Shader *regularShader) {
    for (auto &renderComponent: renderComponents) {
        renderComponent->simpleDraw(*regularShader);
    }
}

void RenderSystem::showImGuiDetails(Camera *camera) {

}

RenderSystem::RenderSystem() {
    name = "Render system";
}

void RenderSystem::addComponent(void *component) {
    renderComponents.push_back(reinterpret_cast<Render *const>(component));
}


void RenderSystem::removeComponent(void *component) {
    auto component_iter = std::find(renderComponents.begin(), renderComponents.end(), reinterpret_cast<Render *const>(component));

    if (component_iter != renderComponents.end()) {
        renderComponents.erase(component_iter);
    }
}
