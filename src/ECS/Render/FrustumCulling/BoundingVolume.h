//
// Created by igork on 03.04.2024.
//

#ifndef ZTGK_BOUNDINGVOLUME_H
#define ZTGK_BOUNDINGVOLUME_H
#include "glm/glm.hpp"
#include "Frustum.h"

struct BoundingVolume
{
    virtual bool isOnFrustum(const Frustum& camFrustum, const Transform& transform) const = 0;

    virtual bool isOnOrForwardPlane(const Plane& plane) const = 0;

    bool isOnFrustum(const Frustum& camFrustum) const
    {
        return (isOnOrForwardPlane(camFrustum.leftFace) &&
                isOnOrForwardPlane(camFrustum.rightFace) &&
                isOnOrForwardPlane(camFrustum.topFace) &&
                isOnOrForwardPlane(camFrustum.bottomFace) &&
                isOnOrForwardPlane(camFrustum.nearFace) &&
                isOnOrForwardPlane(camFrustum.farFace));
    };
};

struct Sphere : public BoundingVolume
{
    glm::vec3 center{ 0.f, 0.f, 0.f };
    float radius{ 0.f };

    Sphere(const glm::vec3& inCenter, float inRadius)
            : BoundingVolume{}, center{ inCenter }, radius{ inRadius }
    {}

    bool isOnOrForwardPlane(const Plane& plane) const final
    {
        return plane.getSignedDistanceToPlane(center) > -radius;
    }

    bool isOnFrustum(const Frustum& camFrustum, const Transform& transform) const final
    {
        //Get global scale thanks to our transform
        const glm::vec3 globalScale = transform.getGlobalScale();

        //Get our global center with process it with the global model matrix of our transform
        const glm::vec3 globalCenter{ transform.getModelMatrix() * glm::vec4(center, 1.f) };

        //To wrap correctly our shape, we need the maximum scale scalar.
        const float maxScale = std::max(std::max(globalScale.x, globalScale.y), globalScale.z);

        //Max scale is assuming for the diameter. So, we need the half to apply it to our radius
        Sphere globalSphere(globalCenter, radius * (maxScale * 0.5f));

        //Check Firstly the result that have the most chance to failure to avoid to call all functions.
        return (globalSphere.isOnOrForwardPlane(camFrustum.leftFace) &&
                globalSphere.isOnOrForwardPlane(camFrustum.rightFace) &&
                globalSphere.isOnOrForwardPlane(camFrustum.farFace) &&
                globalSphere.isOnOrForwardPlane(camFrustum.nearFace) &&
                globalSphere.isOnOrForwardPlane(camFrustum.topFace) &&
                globalSphere.isOnOrForwardPlane(camFrustum.bottomFace));
    };
};

struct SquareAABB : public BoundingVolume
{
    glm::vec3 center{ 0.f, 0.f, 0.f };
    float extent{ 0.f };

    SquareAABB(const glm::vec3& inCenter, float inExtent)
            : BoundingVolume{}, center{ inCenter }, extent{ inExtent }
    {}

    bool isOnOrForwardPlane(const Plane& plane) const final
    {
        // Compute the projection interval radius of b onto L(t) = b.c + t * p.n
        const float r = extent * (std::abs(plane.normal.x) + std::abs(plane.normal.y) + std::abs(plane.normal.z));
        return -r <= plane.getSignedDistanceToPlane(center);
    }

    bool isOnFrustum(const Frustum& camFrustum, const Transform& transform) const final
    {
        //Get global scale thanks to our transform
        const glm::vec3 globalCenter{ transform.getModelMatrix() * glm::vec4(center, 1.f) };

        // Scaled orientation
        const glm::vec3 right = transform.getRight() * extent;
        const glm::vec3 up = transform.getUp() * extent;
        const glm::vec3 forward = transform.getForward() * extent;

        const float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
                            std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
                            std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

        const float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
                            std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
                            std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

        const float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
                            std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
                            std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

        const SquareAABB globalAABB(globalCenter, std::max(std::max(newIi, newIj), newIk));

        return (globalAABB.isOnOrForwardPlane(camFrustum.leftFace) &&
                globalAABB.isOnOrForwardPlane(camFrustum.rightFace) &&
                globalAABB.isOnOrForwardPlane(camFrustum.topFace) &&
                globalAABB.isOnOrForwardPlane(camFrustum.bottomFace) &&
                globalAABB.isOnOrForwardPlane(camFrustum.nearFace) &&
                globalAABB.isOnOrForwardPlane(camFrustum.farFace));
    };
};

struct AABB : public BoundingVolume
{
    glm::vec3 center{ 0.f, 0.f, 0.f };
    glm::vec3 extents{ 0.f, 0.f, 0.f };

    AABB(const glm::vec3& min, const glm::vec3& max)
            : BoundingVolume{}, center{ (max + min) * 0.5f }, extents{ max.x - center.x, max.y - center.y, max.z - center.z }
    {}

    AABB(const glm::vec3& inCenter, float iI, float iJ, float iK)
            : BoundingVolume{}, center{ inCenter }, extents{ iI, iJ, iK }
    {}

    std::array<glm::vec3, 8> getVertice() const
    {
        std::array<glm::vec3, 8> vertice;
        vertice[0] = { center.x - extents.x, center.y - extents.y, center.z - extents.z };
        vertice[1] = { center.x + extents.x, center.y - extents.y, center.z - extents.z };
        vertice[2] = { center.x - extents.x, center.y + extents.y, center.z - extents.z };
        vertice[3] = { center.x + extents.x, center.y + extents.y, center.z - extents.z };
        vertice[4] = { center.x - extents.x, center.y - extents.y, center.z + extents.z };
        vertice[5] = { center.x + extents.x, center.y - extents.y, center.z + extents.z };
        vertice[6] = { center.x - extents.x, center.y + extents.y, center.z + extents.z };
        vertice[7] = { center.x + extents.x, center.y + extents.y, center.z + extents.z };
        return vertice;
    }

    //see https://gdbooks.gitbooks.io/3dcollisions/content/Chapter2/static_aabb_plane.html
    bool isOnOrForwardPlane(const Plane& plane) const final
    {
        // Compute the projection interval radius of b onto L(t) = b.c + t * p.n
        const float r = extents.x * std::abs(plane.normal.x) + extents.y * std::abs(plane.normal.y) +
                        extents.z * std::abs(plane.normal.z);

        return -r <= plane.getSignedDistanceToPlane(center);
    }

    bool isOnFrustum(const Frustum& camFrustum, const Transform& transform) const final
    {
        //Get global scale thanks to our transform
        const glm::vec3 globalCenter{ transform.getModelMatrix() * glm::vec4(center, 1.f) };

        // Scaled orientation
        const glm::vec3 right = transform.getRight() * extents.x;
        const glm::vec3 up = transform.getUp() * extents.y;
        const glm::vec3 forward = transform.getForward() * extents.z;

        const float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
                            std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
                            std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

        const float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
                            std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
                            std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

        const float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
                            std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
                            std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

        const AABB globalAABB(globalCenter, newIi, newIj, newIk);

        return (globalAABB.isOnOrForwardPlane(camFrustum.leftFace) &&
                globalAABB.isOnOrForwardPlane(camFrustum.rightFace) &&
                globalAABB.isOnOrForwardPlane(camFrustum.topFace) &&
                globalAABB.isOnOrForwardPlane(camFrustum.bottomFace) &&
                globalAABB.isOnOrForwardPlane(camFrustum.nearFace) &&
                globalAABB.isOnOrForwardPlane(camFrustum.farFace));
    };
};


AABB generateAABB(const Model& model);

Sphere generateSphereBV(const Model& model);

#endif //ZTGK_BOUNDINGVOLUME_H
