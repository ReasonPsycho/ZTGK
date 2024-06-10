// 
// Created by cheily on 09.04.2024. 
// 
 
#pragma once 
 
#include "ECS/Component.h" 
#include "HudCompType.h" 
 
enum drawMode { 
    TOP_LEFT,    TOP_CENTER,    TOP_RIGHT, 
    MIDDLE_LEFT, CENTER,        MIDDLE_RIGHT, 
    BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT, 
 
    num_modes 
}; 
#define MODE_NAMES {"Top Left", "Top Center", "Top Right", "Middle Left", "Center", "Middle Right", "Bottom Left", "Bottom Center", "Bottom Right"} 
 
 
struct AHUDComponent : public Component { 
    AHUDComponent(hudcType type, unsigned int groupId) : type(type), groupID(groupId) {} 
    virtual ~AHUDComponent() = default; 
 
    hudcType type; 
    unsigned groupID; 
    glm::vec2 pos; 
    drawMode mode = BOTTOM_LEFT; 
}; 
