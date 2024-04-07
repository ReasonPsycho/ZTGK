//
// Created by cheily on 07.04.2024.
//

#pragma once


#include "glm/fwd.hpp"
#include "glm/detail/type_mat4x4.hpp"
#include "ECS/Render/ModelLoading/Shader.h"
#include "ECS/Canvas/Components/Sprite.h"

class SpriteRenderer {

public:
    explicit SpriteRenderer();
    void render(Sprite sprite);

private:
    glm::vec2 canvas_size = { 1920, 1080 };

    unsigned VAO, VBO;
    glm::mat4 projection;

    Shader shader;
};
