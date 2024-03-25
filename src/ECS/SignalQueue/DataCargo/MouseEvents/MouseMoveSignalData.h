//
// Created by cheily on 21.03.2024.
//

#pragma once

#include "ECS/Grid/VectorUtils.h"
#include "../SignalData.h"
#include "ECS/Util.h"

struct MouseMoveSignalData : public SignalData {
    ztgk::Vec2<double> pos;
    ztgk::Vec2<double> prev;

    // PODs can be passed by value
    MouseMoveSignalData(ztgk::Vec2<double> pos, ztgk::Vec2<double> prev, const std::string & message = "");

    [[nodiscard]] std::string to_string() const override {
        return std::format("{{message=\"{}\", pos=({}, {}), prev=({}, {})}}",
                           message, pos.x, pos.y, prev.x, prev.y);
    }

    static Signal signal(ztgk::Vec2<double> pos, ztgk::Vec2<double> prev, const std::string & message = "");
};
