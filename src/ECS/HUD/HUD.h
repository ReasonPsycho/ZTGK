//
// Created by cheily on 08.04.2024.
//

#pragma once


#include "ECS/System.h"
#include "Group.h"
#include "TextRenderer.h"
#include "SpriteRenderer.h"

class HUD : public System {
public:
    std::unordered_map<unsigned, Group> groups;
    std::unique_ptr<TextRenderer> textRenderer;
    std::unique_ptr<SpriteRenderer> spriteRenderer;

    void draw();
    void drawGroup(unsigned groupID);
    Group * addGroup(glm::vec2 offset = {0, 0}, bool hidden = false);

    void init();
    void addComponent(void *component) override;
    void removeComponent(void *component) override;
    const std::type_index *getComponentTypes() override { return reinterpret_cast<const std::type_index *>(&componentTypes); }
    int getNumComponentTypes() override { return 2; }
    void showImGuiDetails(Camera *camera) override;

    std::unordered_map<unsigned, std::vector<Sprite*>> sprites;
    std::unordered_map<unsigned, std::vector<Text*>> texts;

private:
    std::array<std::type_index, 2> componentTypes = {
        std::type_index(typeid(Sprite)),
        std::type_index(typeid(Text))
    };
};
