//
// Created by igork on 03.04.2024.
//

#include "BoxCollider.h"

BoxCollider::BoxCollider(const glm::vec3& center, const glm::vec3& size)
{
    this->center = center;
    this->size = size;
    this->type = ColliderType::BOX;
}