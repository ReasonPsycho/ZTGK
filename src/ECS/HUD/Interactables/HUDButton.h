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
    Sprite * collisionSprite;

    HUDButton(Sprite * collisionSprite, unsigned groupID, std::function<void()> onPress = [](){}, std::function<void()> onRelease = [](){});

    std::function<void()> onPress;
    std::function<void()> onRelease;
};
