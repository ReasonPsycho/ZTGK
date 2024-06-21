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
    inline static const std::string sound_light = "click_light";
    inline static const std::string sound_normal = "click_normal";

    using button_func = std::function<void(HUDButton * self)>;

    Sprite * collisionSprite;

    HUDButton(Sprite * collisionSprite, unsigned groupID, button_func onPress = [](HUDButton * self){}, button_func onRelease = [](HUDButton * self){}, bool hasSound = true);

    button_func _onPress;
    button_func _onRelease;
    void onPress(HUDButton * self); // this was necessary to wrap sound playing
    void onRelease(HUDButton * self); // this was necessary to wrap sound playing

    bool allow_release_outside = false;
    bool has_sound = true;

    void showImGuiDetailsImpl(Camera *camera) override;
};
