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
    using hover_func = std::function<void(HUDHoverable * self)>;

    Sprite * collisionSprite;

    HUDHoverable(Sprite * collisionSprite, unsigned groupID, hover_func onHoverEnter = [](HUDHoverable * self){}, hover_func onHoverExit = [](HUDHoverable * self){});

    hover_func onHoverEnter;
    hover_func onHoverExit;

    void showImGuiDetailsImpl(Camera *camera) override;

};
