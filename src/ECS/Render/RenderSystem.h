//
// Created by redkc on 25/02/2024.
//

#ifndef REASONABLEGL_RENDERSYSTEM_H
#define REASONABLEGL_RENDERSYSTEM_H


#include "ECS/System.h"
#include "Components/Render.h"
#include "Components/BetterSpriteRender.h"
#include "Components/AnimationPlayer.h"
#include "Components/ColorMask.h"
#include "ECS/Render/ModelLoading/Shader.h"
#include "ECS/Render/Pipelines/Phong/PhongPipeline.h"

#include <algorithm>


class RenderSystem : public System  {
public:
    RenderSystem();
    const std::type_index* getComponentTypes() override {return reinterpret_cast<const type_index *>(&componentTypes); };
    int getNumComponentTypes() override { return 4;};
    void addComponent(void* component) override;
    void removeComponent(void* component) override;
    void showImGuiDetailsImpl(Camera *camera) override;
    void DrawScene(Shader *regularShader, Camera *camera);
    void SimpleDrawScene(Shader *regularShader, glm::vec3 viewPos, float farPlane);
    void registerComponents() override{};
    void UpdateImpl() override;
    void removeColorMaskComponent(void* colorMask);
    Model* tileModel;

private:
    
    std::vector<Render *> renderComponents;
    std::vector<ColorMask *> colorMaskComponents;
    std::vector<AnimationPlayer *> animationPlayerComponents;
    std::vector<BetterSpriteRender *> betterRenderPlayerComponents;
    std::array<std::type_index, 4> componentTypes = {
            std::type_index(typeid(Render)),
            std::type_index(typeid(ColorMask)),
            std::type_index(typeid(AnimationPlayer)),
            std::type_index(typeid(BetterSpriteRender)),
    };
};


#endif //REASONABLEGL_RENDERSYSTEM_H
