//
// Created by cheily on 15.05.2024.
//

#include "HUDButton.h"
#include "ECS/HUD/Components/Sprite.h"

HUDButton::HUDButton(Sprite *collisionSprite, unsigned groupID, std::function<void()> onPress, std::function<void()> onRelease)
: AHUDComponent(BUTTON, groupID), collisionSprite(collisionSprite), onPress(std::move(onPress)), onRelease(std::move(onRelease)) {
    name = "Button";
}
