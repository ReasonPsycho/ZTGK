//
// Created by igork on 03.04.2024.
//

#ifndef ZTGK_SPHERECOLLIDER_H
#define ZTGK_SPHERECOLLIDER_H
#include "ECS/Raycasting/Collider.h"

class CollisionSystem;

class SphereCollider : public Collider {
public:
    glm::vec3 center{};
    float radius;
    void drawWire(Shader *shader, Primitives *primitives) override;

    SphereCollider(const glm::vec3& center, float radius, CollisionSystem* collisionSystem);
};


#endif //ZTGK_SPHERECOLLIDER_H
