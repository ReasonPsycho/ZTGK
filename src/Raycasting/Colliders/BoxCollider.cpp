//
// Created by igork on 03.04.2024.
//

#include "BoxCollider.h"
#include "imgui.h"
#include "ECS/Entity.h"
BoxCollider::BoxCollider(const glm::vec3& center, const glm::vec3& size)
{
    this->center = center;
    this->size = size;
    this->type = ColliderType::BOX;
}

void BoxCollider::showImGuiDetails(Camera *camera) {
    Collider::showImGuiDetails(camera);
    ImGui::Text("Center: (%.2f, %.2f, %.2f)", center.x, center.y, center.z);
    ImGui::Text("Size: (%.2f, %.2f, %.2f)", size.x, size.y, size.z);

    ImGui::PopID();
}

BoxCollider::BoxCollider(Entity *entity, glm::vec3 size) {
    this->center = entity->transform.getLocalPosition();
    this->size = size;
    this->type = ColliderType::BOX;

}
