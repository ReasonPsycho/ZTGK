//
// Created by cheily on 10.04.2024.
//

#pragma once


#include "ECS/SignalQueue/DataCargo/SignalData.h"

struct HUDSortZDepthSignalData : public SignalData {
    explicit HUDSortZDepthSignalData(const std::string & message = "");
    static Signal signal(const std::string & message = "");

    // no need to override to string if no extra fields
};
