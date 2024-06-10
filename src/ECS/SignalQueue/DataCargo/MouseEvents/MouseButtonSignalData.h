// 
// Created by cheily on 22.03.2024. 
// 
 
#pragma once 
 
 
#include "../SignalData.h" 
#include "glm/vec2.hpp" 
 
struct MouseButtonSignalData : public SignalData { 
    glm::vec2 pos; 
    // GLFW_MOUSE_BUTTON_XXXXX 
    int button; 
    // GLFW_PRESS, etc 
    int action; 
    // GLFW_MOD_XXXXX 
    int mods; 
 
    MouseButtonSignalData(int button, int action, int mods, glm::vec2 pos, const std::string & message = ""); 
 
    [[nodiscard]] std::string to_string() const override { 
        return std::format("{{message=\"{}\", button={}, action={}, mods={}, pos=({}, {})}}", 
                           message, button, action, mods, pos.x, pos.y); 
    } 
 
    static Signal signal(int button, int action, int mods, glm::vec2 pos, const std::string & message = ""); 
}; 
