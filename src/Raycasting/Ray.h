//
// Created by igork on 03.04.2024.
//

#ifndef ZTGK_RAY_H
#define ZTGK_RAY_H
#include "glm/glm.hpp"
#include "../ECS/Scene.h"
#include "Collider.h"

class Ray {
public:
    glm::vec3 origin;
    glm::vec3 direction;

    Ray(const glm::vec3& origin, const glm::vec3& direction, Scene* scene);


    bool doesCollide(Collider* collider) const;
    glm::vec3 GetRayHit(ColliderType type, Collider* collider) const;

    glm::vec3 RayHitPoint();

private:
    glm::vec3 RayHit;

};


#endif //ZTGK_RAY_H
