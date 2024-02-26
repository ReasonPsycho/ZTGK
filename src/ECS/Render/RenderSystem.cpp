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
