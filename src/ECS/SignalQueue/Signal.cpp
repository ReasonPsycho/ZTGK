//
// Created by cheily on 20.03.2024.
//

#include "Signal.h"
#include "ECS/Utils/Util.h"

using namespace ztgk;


s_signal_types::s_signal_types() {
    test = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    keyboard = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    audio_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();

    mouse_button_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    mouse_move_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    mouse_scroll_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
        all_mouse = mouse_scroll_signal | mouse_move_signal | mouse_button_signal;

    hud_update_group_mappings_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    hud_sort_z_depth_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    hud_remove_group_signal = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
        all_hud = hud_sort_z_depth_signal | hud_update_group_mappings_signal | hud_remove_group_signal;

    level_load = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();
    level_save = mask_id<MASK_ID_POOL_SIGNAL_TYPE>();

    all = test | keyboard | audio_signal | all_mouse | all_hud | level_load | level_save;
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

