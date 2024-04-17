//
// Created by igork on 03.04.2024.
//

#include "BoxCollider.h"
#include "imgui.h"
#include "ECS/Entity.h"
#include "ECS/Raycasting/CollisionSystem.h"

void BoxCollider::showImGuiDetails(Camera *camera) {
//    Collider::showImGuiDetails(camera);
//    ImGui::Text("Center: (%.2f, %.2f, %.2f)", center.x, center.y, center.z);
//    ImGui::Text("Size: (%.2f, %.2f, %.2f)", size.x, size.y, size.z);

}

BoxCollider::BoxCollider(Entity *entity, glm::vec3 size, CollisionSystem *collisionSystem) {
    this->name = "Box Collider";
    this->center = entity->transform.getGlobalPosition();
    this->size = size;
    this->type = ColliderType::BOX;

    collisionSystem->addComponent(this);

}

void BoxCollider::update() {
//    center = getEntity()->transform.getGlobalPosition();
//    size = getEntity()->transform.getLocalScale();
}

void BoxCollider::drawWire(Shader *shader, Primitives *primitives) {
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), size);
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), center);

    shader->setMatrix4("model", false, glm::value_ptr(translation * scale));
    primitives->renderCube();
}

