//
// Created by cheily on 08.04.2024.
//

#include "HUD.h"
using namespace std;

void HUD::init() {
    name = "HUD";

    Group default_group;
    groups[default_group.id] = default_group;
    textRenderer = make_unique<TextRenderer>();
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
    for ( auto & sprite : sprites[groupID] ) {
        spriteRenderer->render(sprite);
    }
    for ( auto & text : texts[groupID] ) {
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
    if ( typeid(component) == typeid(Sprite*) ) {
        auto sprite = *(Sprite*)component;
        sprites[sprite.HUDGroupID].push_back(sprite);
    } else if ( typeid(component) == typeid(Text*) ) {
        auto text = *(Text*)component;
        texts[text.HUDGroupID].push_back(text);
    }
}

void HUD::removeComponent(void *component) {
    if ( typeid(component) == typeid(Sprite*) ) {
        auto sprite = *(Sprite*)component;
        erase_if(sprites[sprite.HUDGroupID], [sprite](const Sprite & spr){ return spr.uniqueID == sprite.uniqueID; });
    } else if ( typeid(component) == typeid(Text*) ) {
        auto text = *(Text*)component;
        erase_if(texts[text.HUDGroupID], [text](const Text & txt) { return txt.uniqueID == text.uniqueID; });
    }
}

void HUD::showImGuiDetails(Camera *camera) {

}
