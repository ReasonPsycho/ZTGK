//
// Created by cheily on 22.03.2024.
//

#pragma once


#include "../SignalData.h"
#include "glm/vec2.hpp"

struct MouseScrollSignalData : SignalData {
    glm::vec2 offset;

    explicit MouseScrollSignalData(glm::vec2 offset, const std::string & message = "");

    [[nodiscard]] std::string to_string() const override {
        return std::format("{{message=\"{}\", offset=({}, {})}}", message, offset.x, offset.y);
    }

    static Signal signal(glm::vec2 offset, const std::string & message = "");
};
