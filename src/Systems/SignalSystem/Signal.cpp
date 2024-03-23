//
// Created by cheily on 20.03.2024.
//

#include "Signal.h"
#include "Systems/Util.h"

using namespace ztgk_util;


s_signal_types::s_signal_types() {
    test_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    keyboard_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    mouse_button_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    mouse_move_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    mouse_scroll_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    audio_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
}

s_signal_types Signal::signal_types{};

struct SignalData {
    long long timestamp = time();
};

Signal::Signal() : sid(id<ID_POOL_SIGNAL>()) {}

Signal::Signal(unsigned int signalType, long long ttl, unsigned int receiverId, const std::function<void()> &callback, const std::string &message)
        : sid(id<ID_POOL_SIGNAL>()), time_to_live(ttl), receiver_id(receiverId), stype(signalType),
          callback(callback), message(message) {}

std::string Signal::to_string() const {
    std::ostringstream oss;
    oss << "{"
        << "type:" << stype << ","
        << "id:" << sid << ","
        << "message:\"" << message << "\","
        << "ttl:" << time_to_live << ","
        << "receiver_id:" << receiver_id
        << "}";
    return oss.str();
}

