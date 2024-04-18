//
// Created by cheily on 21.03.2024.
//

#include "KeySignalData.h"
#include "../Signal.h"

KeySignalData::KeySignalData(int key, int scancode, int action, int mods, const std::string &message)
        : SignalData(message), key(key), scancode(scancode), action(action), mods(mods) {}

Signal KeySignalData::signal(int key, int scancode, int action, int mods, const std::string &message) {
    return {Signal::signal_types.keyboard, std::make_shared<KeySignalData>(key, scancode, action, mods, message)};
}
