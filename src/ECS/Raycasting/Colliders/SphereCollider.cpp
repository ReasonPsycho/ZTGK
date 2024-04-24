//
// Created by igork on 03.04.2024.
//

#include "SphereCollider.h"
#include "ECS/Render/Primitives/Primitives.h"
#include "ECS/Raycasting/CollisionSystem.h"

SphereCollider::SphereCollider(const glm::vec3& center, float radius, CollisionSystem* collisionSystem){
    this->name = "Sphere Collider";
    this->center = center;
    this->radius = radius;
    this->type = ColliderType::SPHERE;

    collisionSystem->addComponent(this);
}
