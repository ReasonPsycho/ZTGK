//
// Created by cheily on 21.03.2024.
//

#pragma once

#include "ECS/Utils/VectorUtils.h"
#include "../SignalData.h"
#include "ECS/Utils/Util.h"
#include "glm/vec2.hpp"

struct MouseMoveSignalData : public SignalData {
    glm::vec2 pos;
    glm::vec2 prev;

    // PODs can be passed by value
    MouseMoveSignalData(glm::vec2 pos, glm::vec2 prev, const std::string & message = "");

    [[nodiscard]] std::string to_string() const override {
        return std::format("{{message=\"{}\", pos=({}, {}), prev=({}, {})}}",
                           message, pos.x, pos.y, prev.x, prev.y);
    }

    static Signal signal(glm::vec2 pos, glm::vec2 prev, const std::string & message = "");
};
