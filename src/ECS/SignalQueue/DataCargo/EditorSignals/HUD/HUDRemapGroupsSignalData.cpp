// 
// Created by cheily on 10.04.2024. 
// 
 
#include "ECS/SignalQueue/Signal.h" 
#include "HUDRemapGroupsSignalData.h" 
#include "ECS/HUD/Components/HudCompType.h" 
 
HUDRemapGroupsSignalData:: 
HUDRemapGroupsSignalData(bool all, unsigned componentId, hudcType componentType, unsigned oldGroup, unsigned newGroup, const std::string &message) 
: SignalData(message), all(all), componentID(componentId), componentType(componentType), oldGroup(oldGroup), newGroup(newGroup) { 
} 
 
HUDRemapGroupsSignalData:: 
HUDRemapGroupsSignalData(const std::string & message) 
: HUDRemapGroupsSignalData(true, -1, hudcType::UNDEFINED, -1, -1, message) { 
} 
 
HUDRemapGroupsSignalData:: 
HUDRemapGroupsSignalData(unsigned componentID, hudcType componentType, unsigned oldGroup, unsigned newGroup, const std::string & message) 
: HUDRemapGroupsSignalData(false, componentID, componentType, oldGroup, newGroup, message) { 
} 
 
Signal HUDRemapGroupsSignalData:: 
signal_all(const std::string &message) { 
    return { Signal::signal_types.hud_update_group_mappings_signal, std::make_shared<HUDRemapGroupsSignalData>(message) }; 
} 
 
Signal 
HUDRemapGroupsSignalData:: 
signal_one(unsigned componentID, hudcType componentType, unsigned oldGroup, unsigned newGroup, const std::string &message) { 
    return { Signal::signal_types.hud_update_group_mappings_signal, std::make_shared<HUDRemapGroupsSignalData>(componentID, componentType, oldGroup, newGroup, message) }; 
} 
 
Signal HUDRemapGroupsSignalData:: 
signal(bool all, unsigned int componentId, hudcType componentType, unsigned int oldGroup, unsigned int newGroup, const std::string &message) { 
    return { Signal::signal_types.hud_update_group_mappings_signal, std::make_shared<HUDRemapGroupsSignalData>(all, componentId, componentType, oldGroup, newGroup, message) }; 
} 
