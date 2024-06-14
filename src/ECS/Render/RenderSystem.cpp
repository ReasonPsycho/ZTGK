//
// Created by redkc on 25/02/2024.
//

#include "RenderSystem.h"
#include "ECS/Utils/Globals.h"


void RenderSystem::DrawScene(Shader *regularShader, Camera *camera) {
    regularShader->use();


    Frustum frustum = createFrustumFromCamera(*camera);

    for (auto &renderComponent: renderComponents) {
        if(!renderComponent->isInFogOfWar){
            renderComponent->draw(*regularShader, &frustum);
        }
    }
    
    
}

void RenderSystem::SimpleDrawScene(Shader *regularShader, glm::vec3 viewPos, float farPlane) {
    for (auto &renderComponent: renderComponents) {
        if (!renderComponent->isInFogOfWar && glm::distance(renderComponent->getEntity()->transform.getGlobalPosition(), viewPos) < farPlane){
            auto rc = renderComponent;
            renderComponent->simpleDraw(*regularShader);
        }
    }
}

void RenderSystem::showImGuiDetailsImpl(Camera *camera) {

    
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

    AnimationPlayer* animationPlayerPtr = dynamic_cast<AnimationPlayer*>(basePtr);
    if(animationPlayerPtr != nullptr)
    {
        animationPlayerComponents.push_back(animationPlayerPtr);
    }
}

void RenderSystem::UpdateImpl() {
    for (auto colorMask: colorMaskComponents) {
            colorMask->Update();
    }

    for (auto animationPlayer: animationPlayerComponents) {
        animationPlayer->Update();
    }
}


void RenderSystem::removeComponent(void *component) {
    auto component_iter = std::find(renderComponents.begin(), renderComponents.end(), reinterpret_cast<Render *const>(component));

    if (component_iter != renderComponents.end()) {
        renderComponents.erase(component_iter);
    }
}

void RenderSystem::removeColorMaskComponent(void *component) {
    auto component_iter = std::find(colorMaskComponents.begin(), colorMaskComponents.end(), reinterpret_cast<ColorMask *const>(component));

    if (component_iter != colorMaskComponents.end()) {
        colorMaskComponents.erase(component_iter);
    }
}
