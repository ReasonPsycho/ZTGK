//
// Created by cheily on 22.03.2024.
//

#include "MouseButtonSignalData.h"
#include "ECS/SignalSystem/Signal.h"

MouseButtonSignalData::MouseButtonSignalData(int button, int action, int mods, const std::string &message)
        : SignalData(message), button(button), action(action), mods(mods) {}

Signal MouseButtonSignalData::signal(int button, int action, int mods, const std::string &message) {
    return {Signal::signal_types.mouse_button_signal, std::make_shared<MouseButtonSignalData>(button, action, mods, message)};
}
