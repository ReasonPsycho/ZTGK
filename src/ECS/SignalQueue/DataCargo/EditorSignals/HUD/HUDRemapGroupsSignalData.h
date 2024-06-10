// 
// Created by cheily on 10.04.2024. 
// 
 
#pragma once 
 
 
#include "ECS/SignalQueue/DataCargo/SignalData.h" 
#include "ECS/HUD/Components/AHUDComponent.h" 
#include "ECS/HUD/Components/HudCompType.h" 
 
struct HUDRemapGroupsSignalData : public SignalData { 
    bool all = false; 
    unsigned componentID; 
    hudcType componentType; 
    unsigned oldGroup; 
    unsigned newGroup; 
 
    // main ctor 
    HUDRemapGroupsSignalData(bool all, unsigned componentId, hudcType componentType, unsigned oldGroup, unsigned newGroup, const std::string & message = ""); 
    // UpdateImpl all ctor 
    explicit HUDRemapGroupsSignalData(const std::string & message = ""); 
    // UpdateImpl one selected ctor 
    HUDRemapGroupsSignalData(unsigned componentID, hudcType componentType, unsigned oldGroup, unsigned newGroup, const std::string & message = ""); 
 
    [[nodiscard]] std::string to_string() const override { 
        return std::format("{{message=\"{}\", all?={}, componentID={}, componentType={}, oldGroupID={}, newGroupID={}}}", 
                   message, all, componentID, (unsigned)componentType, oldGroup, newGroup); 
    } 
 
    static Signal signal_all(const std::string & message = ""); 
    static Signal signal_one(unsigned componentID, hudcType componentType, unsigned oldGroup, unsigned newGroup, const std::string & message = ""); 
    static Signal signal(bool all, unsigned componentId, hudcType componentType, unsigned oldGroup, unsigned newGroup, const std::string & message = ""); 
}; 
