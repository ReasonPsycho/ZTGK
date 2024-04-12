//
// Created by igork on 03.04.2024.
//

#include "SphereCollider.h"
#include "ECS/Render/Primitives/Primitives.h"

SphereCollider::SphereCollider(const glm::vec3& center, float radius){
    this->name = "Sphere Collider";
    this->center = center;
    this->radius = radius;
    this->type = ColliderType::SPHERE;
}

void SphereCollider::drawWire(Shader *shader, Primitives *primitives) {

}
