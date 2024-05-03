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
    this->collisionType = CollisionType::NORMAL;

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), size);
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), center);

    this-> boxColliderData = BoxColliderData(translation * scale,glm::vec4(1,0,0,1));
}

void BoxCollider::UpdateImpl() {
      center = getEntity()->transform.getGlobalPosition();
      size = getEntity()->transform.getLocalScale();

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), size);
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), center);
    boxColliderData = BoxColliderData(translation * scale,boxColliderData.color);
      
}

bool BoxCollider::intersects(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4) {
    // Determine the coordinates of the box collider's vertices
    glm::vec3 vertices[8];
    glm::vec3 halfSize = size * 0.5f;

    vertices[0] = center + glm::vec3(-halfSize.x, -halfSize.y, -halfSize.z);
    vertices[1] = center + glm::vec3(halfSize.x, -halfSize.y, -halfSize.z);
    vertices[2] = center + glm::vec3(halfSize.x, -halfSize.y, halfSize.z);
    vertices[3] = center + glm::vec3(-halfSize.x, -halfSize.y, halfSize.z);
    vertices[4] = center + glm::vec3(-halfSize.x, halfSize.y, -halfSize.z);
    vertices[5] = center + glm::vec3(halfSize.x, halfSize.y, -halfSize.z);
    vertices[6] = center + glm::vec3(halfSize.x, halfSize.y, halfSize.z);
    vertices[7] = center + glm::vec3(-halfSize.x, halfSize.y, halfSize.z);

    // Check if any box collider's vertices are inside the square
    for (int i = 0; i < 8; ++i) {
        if (glm::dot(p2 - p1, vertices[i] - p1) > 0 &&
            glm::dot(p3 - p2, vertices[i] - p2) > 0 &&
            glm::dot(p4 - p3, vertices[i] - p3) > 0 &&
            glm::dot(p1 - p4, vertices[i] - p4) > 0) {
            return true;
        }
    }

    // Check if any square's vertices are inside the box collider
    glm::vec3 squareVertices[] = {p1, p2, p3, p4};
    for (const auto& vertex : squareVertices) {
        if (vertex.x >= center.x - halfSize.x && vertex.x <= center.x + halfSize.x &&
            vertex.y >= center.y - halfSize.y && vertex.y <= center.y + halfSize.y &&
            vertex.z >= center.z - halfSize.z && vertex.z <= center.z + halfSize.z) {
            return true;
        }
    }

    return false;
}

BoxCollider::BoxCollider(Entity *entity, glm::vec3 size, CollisionType type, CollisionSystem *collisionSystem) {
    this->name = "Box Collider";
    this->center = entity->transform.getGlobalPosition();
    this->size = size;
    this->type = ColliderType::BOX;
    this->collisionType = type;
    
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), size);
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), center);

    this-> boxColliderData = BoxColliderData(translation * scale,glm::vec4(1,0,0,1));
}



