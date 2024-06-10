// 
// Created by cheily on 15.05.2024. 
// 
 
#pragma once 
 
#include <functional> 
#include "ECS/Component.h" 
#include "ECS/HUD/Components/AHUDComponent.h" 
 
class Sprite; 
 
class HUDButton : public AHUDComponent { 
public: 
    using button_func = std::function<void(HUDButton * self)>; 
 
    Sprite * collisionSprite; 
 
    HUDButton(Sprite * collisionSprite, unsigned groupID, button_func onPress = [](HUDButton * self){}, button_func onRelease = [](HUDButton * self){}); 
 
    button_func onPress; 
    button_func onRelease; 
    bool allow_release_outside = false; 
 
    void showImGuiDetailsImpl(Camera *camera) override; 
}; 
