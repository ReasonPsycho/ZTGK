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
    void drawWire(Shader* shader);

    glm::vec3 RayHitPoint();
    Entity* getHitEntity();

private:
    float rayPoints[6];
    unsigned int VBO, VAO;
    glm::vec3 RayHit;
    glm::vec3 defaultHit = glm::vec3(std::numeric_limits<float>::infinity());
    Entity* hitEntity = nullptr;
};


#endif //ZTGK_RAY_H
