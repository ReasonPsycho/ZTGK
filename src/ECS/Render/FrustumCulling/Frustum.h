// 
// Created by igork on 03.04.2024. 
// 
 
#ifndef ZTGK_FRUSTUM_H 
#define ZTGK_FRUSTUM_H 
#include "glm/glm.hpp" 
#include "../../Transform/Transform.h" 
#include "../ModelLoading/Model.h" 
 
struct Plane 
{ 
    glm::vec3 normal = { 0.f, 1.f, 0.f }; // unit vector 
    float     distance = 0.f;        // Distance with origin 
 
    Plane() = default; 
 
    Plane(const glm::vec3& p1, const glm::vec3& norm) 
            : normal(glm::normalize(norm)), 
              distance(glm::dot(normal, p1)) 
    {} 
 
    float getSignedDistanceToPlane(const glm::vec3& point) const 
    { 
        return glm::dot(normal, point) - distance; 
    } 
}; 
 
struct Frustum 
{ 
    Plane topFace; 
    Plane bottomFace; 
 
    Plane rightFace; 
    Plane leftFace; 
 
    Plane farFace; 
    Plane nearFace; 
}; 
 
 
 
Frustum createFrustumFromCamera(Camera& cam); 
 
 
 
 
 
#endif //ZTGK_FRUSTUM_H 
