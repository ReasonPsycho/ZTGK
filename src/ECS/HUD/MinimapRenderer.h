//
// Created by cheily on 13.06.2024.
//

#pragma once

#include "glm/fwd.hpp"
#include "ECS/Render/ModelLoading/Shader.h"
#include "ECS/HUD/Components/Minimap.h"

class HUD;

class MinimapRenderer {
public:
    explicit MinimapRenderer(HUD * hud);
    void render(Minimap * minimap);

    HUD * hud;

private:
    unsigned VAO, VBO;
    glm::mat4 projection;

    Shader shader;

    glm::vec2 drawModeOffset(Minimap * minimap) const;
};
