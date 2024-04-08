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



Frustum createFrustumFromCamera(const Camera& cam, float aspect, float fovY, float zNear, float zFar)
{
    Frustum     frustum;
    const float halfVSide = zFar * tanf(fovY * .5f);
    const float halfHSide = halfVSide * aspect;
    const glm::vec3 frontMultFar = zFar * cam.Front;

    frustum.nearFace = { cam.Position + zNear * cam.Front, cam.Front };
    frustum.farFace = { cam.Position + frontMultFar, -cam.Front };
    frustum.rightFace = { cam.Position, glm::cross(frontMultFar - cam.Right * halfHSide, cam.Up) };
    frustum.leftFace = { cam.Position, glm::cross(cam.Up, frontMultFar + cam.Right * halfHSide) };
    frustum.topFace = { cam.Position, glm::cross(cam.Right, frontMultFar - cam.Up * halfVSide) };
    frustum.bottomFace = { cam.Position, glm::cross(frontMultFar + cam.Up * halfVSide, cam.Right) };
    return frustum;
}





#endif //ZTGK_FRUSTUM_H
