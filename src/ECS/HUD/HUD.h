//
// Created by cheily on 08.04.2024.
//

#pragma once


#include "ECS/System.h"
#include "Group.h"
#include "TextRenderer.h"
#include "SpriteRenderer.h"

class HUD : System {
    std::unordered_map<unsigned, Group> groups;
    std::unique_ptr<TextRenderer> textRenderer;
    std::unique_ptr<SpriteRenderer> spriteRenderer;

    Group * addGroup(glm::vec2 offset = {0, 0}, bool hidden = false);

    void init();
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
