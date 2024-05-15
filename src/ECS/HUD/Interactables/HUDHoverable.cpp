//
// Created by cheily on 15.05.2024.
//
#include "HUDHoverable.h"

#include "ECS/HUD/Components/Sprite.h"

HUDHoverable::HUDHoverable(Sprite *collisionSprite, unsigned groupID, std::function<void()> onHoverEnter, std::function<void()> onHoverExit)
: AHUDComponent(HOVERABLE, groupID), collisionSprite(collisionSprite), onHoverEnter(std::move(onHoverEnter)), onHoverExit(std::move(onHoverExit)) {
    name = "Hoverable";
}
