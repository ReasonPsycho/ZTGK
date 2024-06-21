//
// Created by cheily on 15.05.2024.
//

#include "HUDButton.h"
#include "ECS/HUD/HUD.h"
#include "ECS/HUD/Components/Sprite.h"
#include "ECS/Entity.h"

HUDButton::HUDButton(Sprite * collisionSprite, unsigned groupID, button_func onPress, button_func onRelease, bool hasSound)
: AHUDComponent(BUTTON, groupID), collisionSprite(collisionSprite), _onPress(std::move(onPress)), _onRelease(std::move(onRelease)), has_sound(hasSound) {
    name = "Button";
}

void HUDButton::onPress(HUDButton *self) {
    if (has_sound) {
        ztgk::game::audioManager->playSound(sound_normal);
    }
    _onPress(self);
}

void HUDButton::onRelease(HUDButton *self) {
    if (has_sound) {
        ztgk::game::audioManager->playSound(sound_light);
    }
    _onRelease(self);
}

void HUDButton::showImGuiDetailsImpl(Camera *camera) {
    ImGui::Text("Name: %s", name.c_str());
    ImGui::Text("ID: %d", uniqueID);
    if (ImGui::TreeNode(std::format("Sprite used: ID {}, Tex {}", collisionSprite->uniqueID, collisionSprite->texture).c_str())) {
        collisionSprite->showImGuiDetails(camera);
        ImGui::TreePop();
    }
}
