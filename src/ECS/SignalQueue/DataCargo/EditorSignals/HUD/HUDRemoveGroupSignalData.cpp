//
// Created by cheily on 10.04.2024.
//

#include "HUDRemoveGroupSignalData.h"
#include "ECS/SignalQueue/Signal.h"

HUDRemoveGroupSignalData::HUDRemoveGroupSignalData(unsigned int groupId, const std::string & message)
: SignalData(message), groupID(groupId) {}

Signal HUDRemoveGroupSignalData::signal(unsigned int groupID, const std::string &message) {
    return { Signal::signal_types.hud_remove_group_signal, std::make_shared<HUDRemoveGroupSignalData>(groupID) };
}
