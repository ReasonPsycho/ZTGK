//
// Created by igork on 03.04.2024.
//

#include "BoxCollider.h"
#include "imgui.h"
#include "ECS/Entity.h"
#include "ECS/Raycasting/CollisionSystem.h"

void BoxCollider::showImGuiDetailsImpl(Camera *camera) {
//    Collider::showImGuiDetailsImpl(camera);
//
    ImGui::InputFloat3("Center:",glm::value_ptr(center)) ;
    ImGui::InputFloat3("Size: ", glm::value_ptr(size));
    ImGui::InputFloat4("Color: ", glm::value_ptr(boxColliderData.color));
}

BoxCollider::BoxCollider(Entity *entity, glm::vec3 size, CollisionSystem *collisionSystem) {
    this->name = "Box Collider";
    this->center = entity->transform.getGlobalPosition();
    this->size = size;
    this->type = ColliderType::BOX;

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), size);
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), center);

    this-> boxColliderData = BoxColliderData(translation * scale,glm::vec4(1,0,0,0));
}

void BoxCollider::update() {
      center = getEntity()->transform.getGlobalPosition();
      size = getEntity()->transform.getLocalScale();

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), size);
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), center);
    boxColliderData = BoxColliderData(translation * scale,glm::vec4(1,0,0,0));
      
}


