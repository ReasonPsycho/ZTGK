//
// Created by cheily on 21.03.2024.
//
#include "SignalData.h"
#include "ECS/SignalSystem/Signal.h"


SignalData::SignalData(const std::string &message) : message(message) {}

Signal SignalData::signal(const std::string &message) {
    return {0, std::make_shared<SignalData>(message)};
}
