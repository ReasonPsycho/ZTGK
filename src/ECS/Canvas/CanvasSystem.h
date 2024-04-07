//
// Created by cheily on 04.04.2024.
//

#pragma once
#include "ECS/System.h"
#include "Components/Sprite.h"
#include "Components/Text.h"

class Scene;

class CanvasSystem : public System {
public:
    glm::vec2 size;
    glm::vec2 offset;
    Scene * scene;
    Entity * canvas;

    glm::vec3 default_text_color;

    void init(Scene * scene, glm::vec2 size, glm::vec2 offset);
    glm::vec2 getAbsolutePos(glm::vec2 canvas_pos) const;
    glm::vec2 getCanvasPos(glm::vec3 world_pos) const;

    Text * addText(std::string, glm::vec2 pos, glm::vec2 scale, glm::vec3 color, float rotation, unsigned effectFlags);
//    Sprite * addSprite(std::)

// System overrides
    void addComponent(void *component) override;
    void removeComponent(void *component) override;
    const std::type_index *getComponentTypes() override { return reinterpret_cast<const std::type_index *>(&componentTypes); }
    int getNumComponentTypes() override { return 2; }
    void showImGuiDetails(Camera *camera) override;

private:


    std::array<std::type_index, 2> componentTypes = {
        std::type_index(typeid(Sprite)),
        std::type_index(typeid(Text))
    };
};
