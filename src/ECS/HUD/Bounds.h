//
// Created by cheily on 16.05.2024.
//

#pragma once

#include "glm/vec2.hpp"

struct Bounds {
    float top{};
    float bottom{};
    float left{};
    float right{};

    [[nodiscard]] bool contains(glm::vec2 point) const {
        return point.x >= left && point.x <= right && point.y >= bottom && point.y <= top;
    }
};