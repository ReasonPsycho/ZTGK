// 
// Created by cheily on 22.03.2024. 
// 
 
#include "MouseScrollSignalData.h" 
#include "ECS/SignalQueue/Signal.h" 
#include "ECS/Utils/Util.h" 
 
using namespace ztgk; 
 
MouseScrollSignalData::MouseScrollSignalData(glm::vec2 offset, glm::vec2 pos, const std::string & message) : SignalData(message), pos(pos), offset(offset) {} 
 
Signal MouseScrollSignalData::signal(glm::vec2 offset, glm::vec2 pos, const std::string & message) { 
    return {Signal::signal_types.mouse_scroll_signal, std::make_shared<MouseScrollSignalData>(offset, pos, message)}; 
} 
