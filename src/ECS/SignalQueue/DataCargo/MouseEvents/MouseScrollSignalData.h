//
// Created by cheily on 22.03.2024.
//

#pragma once


#include "../SignalData.h"
#include "Utils/Util.h"

struct MouseScrollSignalData : SignalData {
    ztgk::Vec2<double> offset;

    explicit MouseScrollSignalData(ztgk::Vec2<double> offset, const std::string & message = "");

    [[nodiscard]] std::string to_string() const override {
        return std::format("{{message=\"{}\", offset=({}, {})}}", message, offset.x, offset.y);
    }

    static Signal signal(ztgk::Vec2<double> offset, const std::string & message = "");
};
