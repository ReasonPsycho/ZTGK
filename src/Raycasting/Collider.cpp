//
// Created by igork on 03.04.2024.
//

#include "Collider.h"
#include "imgui.h"
#include "ECS/Transform/Transform.h"
#include "ECS/Entity.h"

void Collider::showImGuiDetails(Camera *camera) {
    ImGui::Text("Collider ");
    ImGui::SameLine(); ImGui::Text("Type: %d", type);
    ImGui::Text("UID: %d", uniqueID);

    ImGui::Text("Position: ");
    ImGui::SameLine(); ImGui::Text("X: %f", parentEntity->transform.getLocalPosition().x);
    ImGui::SameLine(); ImGui::Text(" Y: %f", parentEntity->transform.getLocalPosition().y);
    ImGui::SameLine(); ImGui::Text(" Z: %f", parentEntity->transform.getLocalPosition().z);
}

