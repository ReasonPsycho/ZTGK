//
// Created by cheily on 08.04.2024.
//

#pragma once

#include "glm/vec2.hpp"
#include "Utils/Globals.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "glm/detail/type_mat4x4.hpp"

struct Group {
    // auto-init, don't change pls
    unsigned id;

    Group();

    bool isHidden() const;
    void setHidden(bool hidden);

    void imgui_controls();

    bool hidden = false; // don't set this directly
    glm::vec3 offset = {0, 0, 0 };
};