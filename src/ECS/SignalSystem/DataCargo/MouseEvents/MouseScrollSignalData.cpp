//
// Created by cheily on 22.03.2024.
//

#include "MouseScrollSignalData.h"
#include "Systems/SignalSystem/Signal.h"

MouseScrollSignalData::MouseScrollSignalData(Vec2<double> offset, const std::string & message) : SignalData(message), offset(offset) {}

Signal MouseScrollSignalData::signal(Vec2<double> offset, const std::string & message) {
    return {Signal::signal_types.mouse_scroll_signal, std::make_shared<MouseScrollSignalData>(offset, message)};
}
