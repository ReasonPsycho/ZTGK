//
// Created by redkc on 25/02/2024.
//

#include "RenderSystem.h"
#include "ECS/Utils/Globals.h"


void RenderSystem::DrawScene(Shader *regularShader, Camera *camera) {
    regularShader->use();
    regularShader->setFloat("saturationMultiplayer",ztgk::game::saturationMultiplayer);
    regularShader->setFloat("lightMultiplayer",ztgk::game::lightMultiplayer);
    regularShader->setInt("toon_color_levels",ztgk::game::toon_color_levels);

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

void RenderSystem::showImGuiDetailsImpl(Camera *camera) {
    ImGui::SliderFloat("saturationMultiplayer",&ztgk::game::saturationMultiplayer,0,10);
    ImGui::SliderFloat("lightMultiplayer",&ztgk::game::lightMultiplayer,0,10);
    ImGui::InputInt("toon_color_levels",&ztgk::game::toon_color_levels);
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
