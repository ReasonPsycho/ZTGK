//
// Created by cheily on 21.03.2024.
//

#pragma once


#include "SignalData.h"

struct TestSignalData : public SignalData {
    TestSignalData() = default;
    explicit TestSignalData(const std::string & message) : SignalData(message) {}

    static Signal signal();
};
