//
// Created by cheily on 07.04.2024.
//

#include "SpriteRenderer.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ECS/Utils/Globals.h"
#include "HUD.h"

using namespace ztgk;

SpriteRenderer::SpriteRenderer(HUD * hud) : hud(hud), shader("res/shaders/hud_sprite.vert", "res/shaders/hud_sprite.frag") {
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

void SpriteRenderer::render(Sprite * sprite) {
    shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sprite->texture);
    auto group = hud->getGroupOrDefault(sprite->groupID);
    auto pivotOffset = drawModeOffset(sprite);
    float xpos = sprite->pos.x + group->offset.x + pivotOffset.x;
    float ypos = sprite->pos.y + group->offset.y + pivotOffset.y;
    float w = sprite->size.x, h = sprite->size.y;

    float vertices[] = {
            xpos,     ypos + h, 0.0f, 0.0f,
            xpos,     ypos,     0.0f, 1.0f,
            xpos + w, ypos,     1.0f, 1.0f,

            xpos,     ypos + h, 0.0f, 0.0f,
            xpos + w, ypos,     1.0f, 1.0f,
            xpos + w, ypos + h, 1.0f, 0.0f
    };

    shader.setMatrix4("projection", false, glm::value_ptr(projection));
    shader.setVec4("texColor", sprite->color);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void SpriteRenderer::imgui_controls() {
    ImGui::Text("%s", std::format("Shader ID: {}", shader.ID).c_str());
}

glm::vec2 SpriteRenderer::size(Sprite *sprite) const {
    return sprite->size;
}

glm::vec2 SpriteRenderer::drawModeOffset(Sprite *sprite) const {
    auto _size = size(sprite);
    switch (sprite->mode) {
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
