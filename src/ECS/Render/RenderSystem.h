//
// Created by redkc on 25/02/2024.
//

#ifndef REASONABLEGL_RENDERSYSTEM_H
#define REASONABLEGL_RENDERSYSTEM_H


#include "ECS/System.h"
#include "Components/Render.h"
#include "ECS/Render/ModelLoading/Shader.h"

#include <algorithm>


class RenderSystem : public System  {
public:
    RenderSystem();
    const std::type_index* getComponentTypes() override {return reinterpret_cast<const type_index *>(&componentTypes); };
    int getNumComponentTypes() override { return 1;};
    void addComponent(void* component) override;
    void removeComponent(void* component) override;
    void showImGuiDetailsImpl(Camera *camera) override;
    void DrawScene(Shader *regularShader, Camera *camera);
    void SimpleDrawScene(Shader* regularShader);
    void registerComponents() override{};



private:
    float diffuse_levels = 3;
    float specular_levels = 3;
    float light_shade_cutoff = 0.8f;
    float dark_shade_cutoff = 0.5f;


    float rim_threshold = 10;
    float rim_amount = 0.5f;
    
    std::vector<Render *> renderComponents;
    std::array<std::type_index, 1> componentTypes = {
            std::type_index(typeid(Render)),
    };
};


#endif //REASONABLEGL_RENDERSYSTEM_H
