// 
// Created by cheily on 21.05.2024. 
// 
 
#pragma once 
 
#include "ECS/HUD/Components/AHUDComponent.h" 
#include "ECS/SignalQueue/SignalReceiver.h" 
 
class HUDButton; 
class Text; 
class Sprite; 
 
enum SliderStyle { 
    COLOR_BAR, 
    COLOR_BAR_CONTROLLABLE, 
    SETTING_BAR, 
    n_styles 
}; 
#define SLIDER_STYLE_NAMES {"Color Bar", "Color Bar Controllable", "Setting Bar"} 
 
enum SliderDirection{ 
    HORIZONTAL, VERTICAL 
}; 
 
struct HUDSlider : public AHUDComponent { 
 
    float value; 
    SliderDirection direction; 
 
    Sprite * bar; 
    Sprite * barBackground; 
 
    // optional, check control != nullptr 
    HUDButton * control; 
    HUDButton * controlHandle; 
    Sprite * controlHandleForeground; 
 
    bool isListening = false; 
    SignalReceiver * controlListener; 
    void init_control_listener(); 
 
    // optional, check display != nullptr 
    Text * display; 
    float displayMin; 
    float displayMax; 
    std::string displayFormat = "{:.0f}/{:.0f}"; 
 
    HUDSlider(SliderDirection direction, Sprite * displayBar, Sprite * barBackground, unsigned groupID, 
              HUDButton * control = nullptr, HUDButton * controlHandle = nullptr, Sprite * controlHandleForeground = nullptr, 
              Text * display = nullptr, float displayMin = 0, float displayMax = 0); 
 
    void set(float value); 
    void set_in_display_range(float value); 
 
    void set_direction(SliderDirection direction); 
    void set_from_pos(glm::vec2 pos); 
 
    float get_in_display_range() const; 
    std::string get_display_string() const; 
 
    void update_display(); 
 
    void showImGuiDetailsImpl(Camera * camera) override; 
}; 
