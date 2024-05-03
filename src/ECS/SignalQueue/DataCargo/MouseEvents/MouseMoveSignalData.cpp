//
// Created by cheily on 21.03.2024.
//

#include "MouseMoveSignalData.h"
#include "ECS/SignalQueue/Signal.h"
#include "ECS/Utils/Util.h"

using namespace ztgk;

MouseMoveSignalData::MouseMoveSignalData(glm::vec2 pos, glm::vec2 prev, const std::string & message) : SignalData(message), pos(pos), prev(prev) {}

Signal MouseMoveSignalData::signal(glm::vec2 pos, glm::vec2 prev, const std::string & message) {
    return {Signal::signal_types.mouse_move_signal, std::make_shared<MouseMoveSignalData>(pos, prev, message)};
}