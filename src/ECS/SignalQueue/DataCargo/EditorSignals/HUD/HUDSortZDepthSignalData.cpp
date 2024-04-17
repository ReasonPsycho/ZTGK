//
// Created by cheily on 10.04.2024.
//

#include "HUDSortZDepthSignalData.h"
#include "ECS/SignalQueue/Signal.h"

HUDSortZDepthSignalData::HUDSortZDepthSignalData(const std::string & message)
: SignalData(message) {
}

Signal HUDSortZDepthSignalData::signal(const std::string &message) {
    return { Signal::signal_types.hud_sort_z_depth_signal, std::make_shared<HUDSortZDepthSignalData>(message) };
}
