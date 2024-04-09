//
// Created by cheily on 08.04.2024.
//

#include "HUD.h"
using namespace std;

void HUD::init() {
    name = "HUD";

    Group default_group;
    groups[default_group.id] = default_group;
    textRenderer = make_unique<TextRenderer>(this);
    spriteRenderer = make_unique<SpriteRenderer>(this);
}

void HUD::draw() {
    for (auto pair : groups) {
        drawGroup(pair.first);
    }
}

void HUD::drawGroup(unsigned int groupID) {
    if ( !groups.contains(groupID) ) {
        spdlog::warn(std::format("HUD Group {} not found! Defaulting to group 0.", groupID));
        groupID = 0;
    }
    if ( groups[groupID].hidden ) return;
    for ( auto sprite : sprites[groupID] ) {
        spriteRenderer->render(sprite);
    }
    for ( auto text : texts[groupID] ) {
        textRenderer->render(text);
    }
}

Group * HUD::addGroup(glm::vec2 offset, bool hidden) {
    Group newGroup;
    newGroup.offset = offset;
    newGroup.setHidden(hidden);
    groups[newGroup.id] = newGroup;
    return &groups[newGroup.id];
}

void HUD::addComponent(void *component) {
    auto c = static_cast<AHUDComponent*>(component);
    switch (c->type) {
        case AHUDComponent::SPRITE: {
            Sprite * sprite = reinterpret_cast<Sprite*>(component);
            sprites[sprite->groupID].push_back(sprite);
            break;
        }
        case AHUDComponent::TEXT: {
            Text * text = reinterpret_cast<Text*>(component);
            texts[text->groupID].push_back(text);
            break;
        }
    }
}

void HUD::removeComponent(void *component) {
    auto c = (AHUDComponent*)component;
    switch (c->type) {
        case AHUDComponent::SPRITE: {
            erase(sprites[c->groupID], dynamic_cast<Sprite *>(c));
            break;
        }
        case AHUDComponent::TEXT: {
            erase(texts[c->groupID], dynamic_cast<Text *>(c));
            break;
        }
    }
}

void HUD::showImGuiDetails(Camera *camera) {

}
