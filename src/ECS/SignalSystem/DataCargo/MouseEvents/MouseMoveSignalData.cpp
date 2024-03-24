//
// Created by cheily on 21.03.2024.
//

#include "MouseMoveSignalData.h"
#include "ECS/SignalSystem/Signal.h"
#include "ECS/Util.h"

using namespace ztgk;

MouseMoveSignalData::MouseMoveSignalData(Vec2<double> pos, Vec2<double> prev, const std::string & message) : SignalData(message), pos(pos), prev(prev) {}

Signal MouseMoveSignalData::signal(Vec2<double> pos, Vec2<double> prev, const std::string & message) {
    return {Signal::signal_types.mouse_move_signal, std::make_shared<MouseMoveSignalData>(pos, prev, message)};
}