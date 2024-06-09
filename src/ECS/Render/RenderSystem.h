//
// Created by redkc on 25/02/2024.
//

#ifndef REASONABLEGL_RENDERSYSTEM_H
#define REASONABLEGL_RENDERSYSTEM_H


#include "ECS/System.h"
#include "Components/Render.h"
#include "Components/AnimationPlayer.h"
#include "Components/ColorMask.h"
#include "ECS/Render/ModelLoading/Shader.h"

#include <algorithm>


class RenderSystem : public System  {
public:
    RenderSystem();
    const std::type_index* getComponentTypes() override {return reinterpret_cast<const type_index *>(&componentTypes); };
    int getNumComponentTypes() override { return 3;};
    void addComponent(void* component) override;
    void removeComponent(void* component) override;
    void showImGuiDetailsImpl(Camera *camera) override;
    void DrawScene(Shader *regularShader, Camera *camera);
    void SimpleDrawScene(Shader* regularShader);
    void registerComponents() override{};
    void UpdateImpl() override;


private:
    std::vector<Render *> renderComponents;
    std::vector<ColorMask *> colorMaskComponents;
    std::vector<ColorMask *> animationPlayerComponents;
    std::array<std::type_index, 3> componentTypes = {
            std::type_index(typeid(Render)),
            std::type_index(typeid(ColorMask)),
            std::type_index(typeid(AnimationPlayer)),
    };
};


#endif //REASONABLEGL_RENDERSYSTEM_H
