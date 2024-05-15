//
// Created by cheily on 07.04.2024.
//

#pragma once
#include "glm/fwd.hpp"
#include "glm/detail/type_mat4x4.hpp"
#include "ECS/Render/ModelLoading/Shader.h"
#include "ECS/HUD/Components/Sprite.h"
class HUD;

class SpriteRenderer {

public:
    explicit SpriteRenderer(HUD * hud);
    void render(Sprite * sprite);

    HUD * hud;

    glm::vec2 size(Sprite * sprite) const;
    // editor
    void imgui_controls();
private:
    unsigned VAO, VBO;
    glm::mat4 projection;

    Shader shader;

    glm::vec2 drawModeOffset(Sprite * sprite) const;
};
