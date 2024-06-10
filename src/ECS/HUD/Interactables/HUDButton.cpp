// 
// Created by cheily on 15.05.2024. 
// 
 
#include "HUDButton.h" 
#include "ECS/HUD/HUD.h" 
#include "ECS/HUD/Components/Sprite.h" 
#include "ECS/Entity.h" 
 
HUDButton::HUDButton(Sprite * collisionSprite, unsigned groupID, button_func onPress, button_func onRelease) 
: AHUDComponent(BUTTON, groupID), collisionSprite(collisionSprite), onPress(std::move(onPress)), onRelease(std::move(onRelease)) { 
    name = "Button"; 
} 
 
void HUDButton::showImGuiDetailsImpl(Camera *camera) { 
    ImGui::Text("Name: %s", name.c_str()); 
    ImGui::Text("ID: %d", uniqueID); 
    if (ImGui::TreeNode(std::format("Sprite used: ID {}, Tex {}", collisionSprite->uniqueID, collisionSprite->texture).c_str())) { 
        collisionSprite->showImGuiDetails(camera); 
        ImGui::TreePop(); 
    } 
} 
