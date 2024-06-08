//
// Created by redkc on 25/02/2024.
//

#include "RenderSystem.h"
#include "ECS/Utils/Globals.h"


void RenderSystem::DrawScene(Shader *regularShader, Camera *camera) {
    regularShader->use();


    Frustum frustum = createFrustumFromCamera(*camera);
    for (auto &renderComponent: renderComponents) {
        renderComponent->draw(*regularShader, &frustum);
    }
    
    
}

void RenderSystem::SimpleDrawScene(Shader *regularShader) {
    for (auto &renderComponent: renderComponents) {
        auto rc = renderComponent;
        renderComponent->simpleDraw(*regularShader);
    }
}

void RenderSystem::showImGuiDetailsImpl(Camera *camera) {
    ImGui::SliderFloat("saturationMultiplayer", &ztgk::game::saturationMultiplayer, 0, 10);
    ImGui::SliderFloat("lightMultiplayer", &ztgk::game::lightMultiplayer, 0, 10);
    ImGui::InputInt("toon_color_levels", &ztgk::game::toon_color_levels);
    
}

RenderSystem::RenderSystem() {
    name = "Render system";
}

void RenderSystem::addComponent(void *component) {
    Component* basePtr = static_cast<Component*>(component);

    Render* renderPtr = dynamic_cast<Render*>(basePtr);
    if(renderPtr != nullptr)
    {
        renderComponents.push_back(renderPtr);
    }

    ColorMask* colorMaskPtr = dynamic_cast<ColorMask*>(basePtr);
    if(colorMaskPtr != nullptr)
    {
        colorMaskComponents.push_back(colorMaskPtr);
    }
}

void RenderSystem::UpdateImpl() {
    for (auto colorMask: colorMaskComponents) {
            colorMask->Update();
    }
}


void RenderSystem::removeComponent(void *component) {
    auto component_iter = std::find(renderComponents.begin(), renderComponents.end(), reinterpret_cast<Render *const>(component));

    if (component_iter != renderComponents.end()) {
        renderComponents.erase(component_iter);
    }
}
