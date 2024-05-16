//
// Created by cheily on 15.05.2024.
//

#pragma once

#include <functional>
#include "ECS/Component.h"
#include "ECS/HUD/Components/AHUDComponent.h"

class Sprite;

class HUDHoverable : public AHUDComponent {
public:
    Sprite * collisionSprite;

    HUDHoverable(Sprite * collisionSprite, unsigned groupID, std::function<void()> onHoverEnter = [](){}, std::function<void()> onHoverExit = [](){});

    std::function<void()> onHoverEnter;
    std::function<void()> onHoverExit;

    void showImGuiDetailsImpl(Camera *camera) override;

};
