//
// Created by igork on 03.04.2024.
//

#include "BoxCollider.h"
#include "imgui.h"
#include "ECS/Entity.h"


void BoxCollider::showImGuiDetails(Camera *camera) {
    Collider::showImGuiDetails(camera);
    ImGui::Text("Center: (%.2f, %.2f, %.2f)", center.x, center.y, center.z);
    ImGui::Text("Size: (%.2f, %.2f, %.2f)", size.x, size.y, size.z);

}

BoxCollider::BoxCollider(Entity *entity, glm::vec3 size, Model* pModel) {
    this->name = "Box Collider";
    this->center = entity->transform.getLocalPosition();
    this->size = size;
    this->type = ColliderType::BOX;
    this->model = pModel;
    this->render = std::make_unique<Render>(Render(pModel));
    this->render->parentEntity = entity;
    this->render->name = "Box Collider Render";

}

void BoxCollider::update() {
    center = getEntity()->transform.getLocalPosition();
}

