//
// Created by cheily on 21.03.2024.
//

#pragma once


#include "SignalData.h"

struct KeySignalData : public SignalData {
    int key;
    int scancode;
    int action;
    int mods;

    KeySignalData(int key, int scancode, int action, int mods, const std::string & message = "");

    [[nodiscard]] std::string to_string() const override {
        return std::format("{{message=\"{}\", key={}, scancode={}, action={}, mods={}}}",
                           message, key, scancode, action, mods);
    }

    static Signal signal(int key, int scancode, int action, int mods, const std::string & message = "");
};
