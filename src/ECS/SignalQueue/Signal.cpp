//
// Created by cheily on 20.03.2024.
//

#include "Signal.h"
#include "ECS/Util.h"

using namespace ztgk;


s_signal_types::s_signal_types() {
    test_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    keyboard_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    mouse_button_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    mouse_move_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    mouse_scroll_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    audio_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();

    all_mouse = mouse_scroll_signal | mouse_move_signal | mouse_button_signal;
    all = test_signal | keyboard_signal | all_mouse | audio_signal;
}

s_signal_types Signal::signal_types{};

Signal::Signal() : sid(id<ID_POOL_SIGNAL>()), created(time()) {}

Signal::Signal(unsigned int signalType, long long ttl, unsigned int receiverId, const std::shared_ptr<SignalData> & data,
               const std::function<void()> &callback)
        : sid(id<ID_POOL_SIGNAL>()), created(time()), time_to_live(ttl), receiver_id(receiverId), stype(signalType),
          data(data), callback(callback) {}

std::string Signal::to_string() const {
    std::ostringstream oss;
    oss << "{"
        << "type=" << stype << ","
        << "id=" << sid << ","
        << "created=" << created << ","
        << "ttl=" << time_to_live << ","
        << "consume=" << consume << ","
        << "receiver_id=" << receiver_id << ","
        << "data=" << data->to_string() << ","
        << "hasCallback=" << bool(callback)
        << "}";
    return oss.str();
}

Signal::Signal(unsigned int signalType, const std::shared_ptr<SignalData> & data) : Signal(signalType, 0, 0, data,
                                                                                           nullptr) {}

