//
// Created by cheily on 07.04.2024.
//

#pragma once


#include "glm/fwd.hpp"
#include "glm/detail/type_mat4x4.hpp"
#include "ECS/Render/ModelLoading/Shader.h"
#include "ECS/HUD/Components/Sprite.h"
//#include "HUD.h"
class HUD;

class SpriteRenderer {

public:
    explicit SpriteRenderer(HUD * hud);
    void render(Sprite * sprite);

    HUD * hud;
private:
    unsigned VAO, VBO;
    glm::mat4 projection;

    Shader shader;
};
