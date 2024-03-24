//
// Created by cheily on 22.03.2024.
//

#pragma once


#include "Systems/SignalSystem/DataCargo/SignalData.h"

struct MouseButtonSignalData : public SignalData {
    int button;
    int action;
    int mods;

    MouseButtonSignalData(int button, int action, int mods, const std::string & message = "");

    [[nodiscard]] std::string to_string() const override {
        return std::format("{{message=\"{}\", button={}, action={}, mods={}}}",
                           message, button, action, mods);
    }

    static Signal signal(int button, int action, int mods, const std::string & message = "");
};
