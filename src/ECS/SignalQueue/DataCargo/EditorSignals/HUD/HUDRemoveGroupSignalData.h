//
// Created by cheily on 10.04.2024.
//

#pragma once


#include "ECS/SignalQueue/DataCargo/SignalData.h"

struct HUDRemoveGroupSignalData : public SignalData {
    unsigned groupID;

    explicit HUDRemoveGroupSignalData(unsigned int groupId, const std::string & message = "");

    [[nodiscard]] std::string to_string() const override {
        return std::format("{{message=\"{}\", groupdID={}}}",
                   message, groupID);
    }

    static Signal signal(unsigned groupID, const std::string & message = "");
};
