// 
// Created by cheily on 15.05.2024. 
// 
#include "HUDHoverable.h" 
 
#include "ECS/HUD/Components/Sprite.h" 
 
HUDHoverable::HUDHoverable(Sprite * collisionSprite, unsigned groupID, hover_func onHoverEnter, hover_func onHoverExit) 
: AHUDComponent(HOVERABLE, groupID), collisionSprite(collisionSprite), onHoverEnter(std::move(onHoverEnter)), onHoverExit(std::move(onHoverExit)) { 
    name = "Hoverable"; 
} 
 
void HUDHoverable::showImGuiDetailsImpl(Camera *camera) { 
    ImGui::Text("Name: %s", name.c_str()); 
    ImGui::Text("ID: %d", uniqueID); 
    if (ImGui::TreeNode(std::format("Sprite used: ID {}, Tex {}", collisionSprite->uniqueID, collisionSprite->texture).c_str())) { 
        collisionSprite->showImGuiDetails(camera); 
        ImGui::TreePop(); 
    } 
} 
