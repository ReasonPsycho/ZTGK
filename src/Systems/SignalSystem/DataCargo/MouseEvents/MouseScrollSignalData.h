//
// Created by cheily on 22.03.2024.
//

#pragma once


#include "ECS/Grid/VectorUtils.h"
#include "Systems/SignalSystem/DataCargo/SignalData.h"

struct MouseScrollSignalData : SignalData {
    Vec2<double> offset;

    MouseScrollSignalData(Vec2<double> offset, const std::string & message = "");

    [[nodiscard]] std::string to_string() const override {
        return std::format("{{message=\"{}\", offset=({}, {})}}", message, offset.x, offset.y);
    }

    static Signal signal(Vec2<double> offset, const std::string & message = "");
};
