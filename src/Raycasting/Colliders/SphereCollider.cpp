//
// Created by igork on 03.04.2024.
//

#include "SphereCollider.h"

SphereCollider::SphereCollider(const glm::vec3& center, float radius){
    this->center = center;
    this->radius = radius;
    this->type = ColliderType::SPHERE;
}