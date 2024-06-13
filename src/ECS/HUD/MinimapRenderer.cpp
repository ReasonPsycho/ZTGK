//
// Created by cheily on 13.06.2024.
//

#include "MinimapRenderer.h"
#include "ECS/Utils/Globals.h"

using namespace ztgk;

MinimapRenderer::MinimapRenderer(HUD *hud) : hud(hud), shader("res/shaders/hud_sprite.vert", "res/shaders/hud_sprite.frag") {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    projection = glm::ortho(0.0f, (float)game::window_size.x, 0.0f, (float)game::window_size.y);
    shader.init();
}

void MinimapRenderer::render(Minimap *minimap) {

}

glm::vec2 MinimapRenderer::drawModeOffset(Minimap *minimap) const {
    auto _size = minimap->size;
    switch (minimap->mode) {
        case TOP_LEFT:
            return { 0, -_size.y };
        case TOP_CENTER:
            return { -_size.x / 2, -_size.y };
        case TOP_RIGHT:
            return { -_size.x, -_size.y };
        case MIDDLE_LEFT:
            return { 0, -_size.y / 2 };
        case CENTER:
            return { -_size.x / 2, -_size.y / 2 };
        case MIDDLE_RIGHT:
            return { -_size.x, -_size.y / 2 };
        default:
        case BOTTOM_LEFT:
            return { 0, 0 };
        case BOTTOM_CENTER:
            return { -_size.x / 2, 0 };
        case BOTTOM_RIGHT:
            return { -_size.x, 0 };
    }
}
