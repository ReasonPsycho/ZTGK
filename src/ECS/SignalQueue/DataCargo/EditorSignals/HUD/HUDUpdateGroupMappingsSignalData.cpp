//
// Created by cheily on 10.04.2024.
//

#include "ECS/SignalQueue/Signal.h"
#include "HUDUpdateGroupMappingsSignalData.h"

HUDUpdateGroupMappingsSignalData::
HUDUpdateGroupMappingsSignalData(bool all, unsigned componentId, unsigned oldGroup, unsigned newGroup, const std::string &message)
: SignalData(message), all(all), componentID(componentId), oldGroup(oldGroup), newGroup(newGroup) {
}

HUDUpdateGroupMappingsSignalData::
HUDUpdateGroupMappingsSignalData(const std::string & message)
: HUDUpdateGroupMappingsSignalData(true, -1, -1, -1, message) {
}

HUDUpdateGroupMappingsSignalData::
HUDUpdateGroupMappingsSignalData(unsigned componentID, unsigned oldGroup, unsigned newGroup, const std::string & message)
: HUDUpdateGroupMappingsSignalData(false, componentID, oldGroup, newGroup, message) {
}

Signal HUDUpdateGroupMappingsSignalData::
signal_all(const std::string &message) {
    return { Signal::signal_types.hud_update_group_mappings_signal, std::make_shared<HUDUpdateGroupMappingsSignalData>(message) };
}

Signal
HUDUpdateGroupMappingsSignalData::
signal_one(unsigned componentID, unsigned oldGroup, unsigned newGroup, const std::string &message) {
    return { Signal::signal_types.hud_update_group_mappings_signal, std::make_shared<HUDUpdateGroupMappingsSignalData>(componentID, oldGroup, newGroup, message) };
}

Signal HUDUpdateGroupMappingsSignalData::
signal(bool all, unsigned int componentId, unsigned int oldGroup, unsigned int newGroup, const std::string &message) {
    return { Signal::signal_types.hud_update_group_mappings_signal, std::make_shared<HUDUpdateGroupMappingsSignalData>(all, componentId, oldGroup, newGroup, message) };
}
