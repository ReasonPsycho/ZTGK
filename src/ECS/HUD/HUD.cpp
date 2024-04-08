//
// Created by cheily on 08.04.2024.
//

#include "HUD.h"
using namespace std;

void HUD::init() {
    Group canvas;
    groups[canvas.id] = canvas;
    textRenderer = make_unique<TextRenderer>();
    spriteRenderer = make_unique<SpriteRenderer>();
}

Group * HUD::addGroup(glm::vec2 offset, bool hidden) {
    Group canvas;
    canvas.offset = offset;
    canvas.setHidden(hidden);
    groups[canvas.id] = canvas;
    return &groups[canvas.id];
}

void HUD::addComponent(void *component) {

}

void HUD::removeComponent(void *component) {

}

void HUD::showImGuiDetails(Camera *camera) {

}
