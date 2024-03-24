//
// Created by redkc on 25/02/2024.
//

#ifndef REASONABLEGL_RENDERSYSTEM_H
#define REASONABLEGL_RENDERSYSTEM_H


#include "ECS/System.h"
#include "Components/Render.h"
#include "ECS/Render/ModelLoading/Shader.h"

class RenderSystem : public System  {



public:
    const std::type_index* getComponentTypes() override {return reinterpret_cast<const type_index *>(&componentTypes); };
    int getNumComponentTypes() override { return 1;};
    void addComponent(void* component) override;
    
    void DrawScene(Shader* regularShader);
    void SimpleDrawScene(Shader* regularShader);

private:
    std::vector<Render *> renderComponents;
    std::array<std::type_index, 1> componentTypes = {
            std::type_index(typeid(Render))
    };
};


#endif //REASONABLEGL_RENDERSYSTEM_H
