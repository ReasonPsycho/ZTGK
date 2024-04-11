//
// Created by cheily on 10.04.2024.
//

#pragma once


#include "ECS/SignalQueue/DataCargo/SignalData.h"

struct HUDUpdateGroupMappingsSignalData : public SignalData {
    bool all = false;
    unsigned componentID;
    unsigned oldGroup;
    unsigned newGroup;

    // main ctor
    HUDUpdateGroupMappingsSignalData(bool all, unsigned componentId, unsigned oldGroup, unsigned newGroup, const std::string & message = "");
    // update all ctor
    explicit HUDUpdateGroupMappingsSignalData(const std::string & message = "");
    // update one selected ctor
    HUDUpdateGroupMappingsSignalData(unsigned componentID, unsigned oldGroup, unsigned newGroup, const std::string & message = "");

    [[nodiscard]] std::string to_string() const override {
        return std::format("{{message=\"{}\", all?={}, componentID={}, oldGroupID={}, newGroupID={}}}",
                   message, all, componentID, oldGroup, newGroup);
    }

    static Signal signal_all(const std::string & message = "");
    static Signal signal_one(unsigned componentID, unsigned oldGroup, unsigned newGroup, const std::string & message = "");
    static Signal signal(bool all, unsigned componentId, unsigned oldGroup, unsigned newGroup, const std::string & message = "");
};
