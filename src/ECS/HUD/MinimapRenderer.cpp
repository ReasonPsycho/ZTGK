//
// Created by cheily on 13.06.2024.
//

#include "MinimapRenderer.h"
#include "ECS/Utils/Globals.h"
#include "ECS/HUD/HUD.h"

using namespace ztgk;

MinimapRenderer::MinimapRenderer(HUD *hud) : hud(hud), shader("res/shaders/hud_minimap.vert", "res/shaders/hud_minimap.frag") {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    projection = glm::ortho(0.0f, (float)game::window_size.x, 0.0f, (float)game::window_size.y);
    shader.init();
}

void MinimapRenderer::render(Minimap *minimap) {
    shader.use();
    auto pivotOffset = drawModeOffset(minimap);
    auto groupOffset = hud->getGroupTreeOffset(minimap->groupID);
    float xpos = minimap->pos.x + groupOffset.x + pivotOffset.x;
    float ypos = minimap->pos.y + groupOffset.y + pivotOffset.y;
//    float w = minimap->size.x, h = minimap->size.y;
    glm::vec2 cellSize = minimap->size / 100.0f;
    float vertices[6 * 100 * 100];

    for (int y = 0; y < 100; ++y) {
        for (int x = 0; x < 100; ++x) {
            vertices[(y * 100 + x) * 6] = xpos + x * cellSize.x;
            vertices[(y * 100 + x) * 6 + 1] = ypos + y * cellSize.y;
            vertices[(y * 100 + x) * 6 + 2] = minimap->colors[y][x].r;
            vertices[(y * 100 + x) * 6 + 3] = minimap->colors[y][x].g;
            vertices[(y * 100 + x) * 6 + 4] = minimap->colors[y][x].b;
            vertices[(y * 100 + x) * 6 + 5] = minimap->colors[y][x].a;
        }
    }

//    float vertices[] = {
//            xpos,     ypos + h, 0.0f, 0.0f,
//            xpos,     ypos,     0.0f, 1.0f,
//            xpos + w, ypos,     1.0f, 1.0f,
//
//            xpos,     ypos + h, 0.0f, 0.0f,
//            xpos + w, ypos,     1.0f, 1.0f,
//            xpos + w, ypos + h, 1.0f, 0.0f
//    };

    shader.setMatrix4("projection", false, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
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
