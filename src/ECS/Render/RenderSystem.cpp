//
// Created by redkc on 25/02/2024.
//

#include "RenderSystem.h"


void RenderSystem::DrawScene(Shader *regularShader, Camera *camera) {
    regularShader->use();

    Frustum frustum = createFrustumFromCamera(*camera);

    for (auto &renderComponent: renderComponents) {
        if(!renderComponent->isInFogOfWar){
            renderComponent->draw(*regularShader, &frustum);
        }
    }
    PhongPipeline *phongPipline = systemManager->getSystem<PhongPipeline>();\
    glEnable(GL_BLEND);
    glDisablei(GL_BLEND, phongPipline->colorAttachments[2]);
    for (auto & betterRender: betterRenderPlayerComponents) {
        if(betterRender!= nullptr && betterRender->getEntity() != nullptr) {
            if (betterRender->draw(ztgk::game::scene->systemManager.getSystem<PhongPipeline>()->spriteRenderShader,
                                   &frustum)) {
                glBindVertexArray(tileModel->meshes[0].VAO);
                glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(tileModel->meshes[0].indices.size()),
                               GL_UNSIGNED_INT, (void *) 0);
                glBindVertexArray(0);
            }
        }
    }
    glDisable(GL_BLEND);


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

    BetterSpriteRender* BetterRenderPtr = dynamic_cast<BetterSpriteRender*>(basePtr);
    if(BetterRenderPtr != nullptr)
    {
        betterRenderPlayerComponents.push_back(BetterRenderPtr);
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

    std::vector<BetterSpriteRender *> toBeDeleted;
    for (auto betterSprite: betterRenderPlayerComponents) {
        if (betterSprite->toBeDeleted) {
            toBeDeleted.push_back(betterSprite);
            continue;
        }
        betterSprite->Update();
    }

    //delete all BetterSptiteRenderers that are marked to be deleted
    for (auto betterSprite: toBeDeleted) {
        betterSprite->Remove();
    }
}


void RenderSystem::removeComponent(void *component) {
    auto component_iter = std::find(renderComponents.begin(), renderComponents.end(), reinterpret_cast<Render *const>(component));

    if (component_iter != renderComponents.end()) {
        renderComponents.erase(component_iter);
    }

    auto BetterSpriteRender_iter = std::find(betterRenderPlayerComponents.begin(), betterRenderPlayerComponents.end(), reinterpret_cast<BetterSpriteRender *const>(component));

    if (BetterSpriteRender_iter != betterRenderPlayerComponents.end()) {
        betterRenderPlayerComponents.erase(BetterSpriteRender_iter);
    }

    auto ColorMask_iter = std::find(colorMaskComponents.begin(), colorMaskComponents.end(), reinterpret_cast<ColorMask *const>(component));

    if (ColorMask_iter != colorMaskComponents.end()) {
        colorMaskComponents.erase(ColorMask_iter);
    }

    auto AnimationPlayer_iter = std::find(animationPlayerComponents.begin(), animationPlayerComponents.end(), reinterpret_cast<AnimationPlayer *const>(component));

    if (AnimationPlayer_iter != animationPlayerComponents.end()) {
        animationPlayerComponents.erase(AnimationPlayer_iter);
    }
}

void RenderSystem::removeColorMaskComponent(void *component) {
    auto component_iter = std::find(colorMaskComponents.begin(), colorMaskComponents.end(), reinterpret_cast<ColorMask *const>(component));

    if (component_iter != colorMaskComponents.end()) {
        colorMaskComponents.erase(component_iter);
    }
}
