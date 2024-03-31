//
// Created by redkc on 25/02/2024.
//

#include "RenderSystem.h"

void RenderSystem::addComponent(void *component) {
    renderComponents.push_back(reinterpret_cast<Render *const>(component));
}

void RenderSystem::DrawScene(Shader *regularShader) {
    for (auto &renderComponent: renderComponents) {
        renderComponent->draw(*regularShader);
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
