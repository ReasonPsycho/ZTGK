//
// Created by cheily on 22.03.2024.
//

#pragma once


#include "../SignalData.h"
#include "glm/vec2.hpp"

struct MouseScrollSignalData : SignalData {
    glm::vec2 pos;
    glm::vec2 offset;

    explicit MouseScrollSignalData(glm::vec2 offset, glm::vec2 pos, const std::string & message = "");

    [[nodiscard]] std::string to_string() const override {
        return std::format("{{message=\"{}\", offset=({}, {}), pos=({}, {})}}", message, offset.x, offset.y, pos.x, pos.y);
    }

    static Signal signal(glm::vec2 offset, glm::vec2 pos, const std::string & message = "");
};
