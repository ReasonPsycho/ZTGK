//
// Created by cheily on 04.04.2024.
//

#pragma once

#include <string>
//#include <gl/GL.h>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glad/glad.h"

struct Sprite {
    glm::vec2 pos = { 500, 500 };
    glm::vec2 size = {};
    GLuint texture;
    glm::vec3 color = { 1, 1, 1 };
    unsigned HUDGroupID = 0;

    void load(const std::string & path);
};
