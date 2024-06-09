//
// Created by redkc on 25/02/2024.
//

#ifndef REASONABLEGL_RENDERSYSTEM_H
#define REASONABLEGL_RENDERSYSTEM_H


#include "ECS/System.h"
#include "Components/Render.h"
#include "Components/ColorMask.h"
#include "ECS/Render/ModelLoading/Shader.h"

#include <algorithm>


class RenderSystem : public System  {
public:
    RenderSystem();
    const std::type_index* getComponentTypes() override {return reinterpret_cast<const type_index *>(&componentTypes); };
    int getNumComponentTypes() override { return 2;};
    void addComponent(void* component) override;
    void removeComponent(void* component) override;
    void showImGuiDetailsImpl(Camera *camera) override;
    void DrawScene(Shader *regularShader, Camera *camera);
    void SimpleDrawScene(Shader* regularShader);
    void registerComponents() override{};
    void UpdateImpl() override;
    void removeColorMaskComponent(void* colorMask);


private:
    std::vector<Render *> renderComponents;
    std::vector<ColorMask *> colorMaskComponents;
    std::array<std::type_index, 2> componentTypes = {
            std::type_index(typeid(Render)),
            std::type_index(typeid(ColorMask)),
    };
};


#endif //REASONABLEGL_RENDERSYSTEM_H
