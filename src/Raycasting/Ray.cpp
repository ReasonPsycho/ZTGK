//
// Created by igork on 03.04.2024.
//

#include "Ray.h"
#include "Collider.h"
#include "Colliders/BoxCollider.h"
#include "Raycasting/Colliders/SphereCollider.h"

/**
 * @brief Ray constructor
 * @param origin
 * @param direction
 * @param scene
 */
Ray::Ray(const glm::vec3& origin, const glm::vec3& direction, Scene* scene)
{
    this->origin = origin;
    this->direction = direction;

    std::vector<Collider*> colliders = scene->getColliders();

    for (auto & collider : colliders)
    {
        if (collider->type == ColliderType::BOX && doesCollide(collider))
        {
            RayHit = GetRayHit(ColliderType::BOX, collider);
        }
        else if(collider->type == ColliderType::SPHERE && doesCollide(collider))
        {
            RayHit = GetRayHit(ColliderType::SPHERE, collider);
        }
    }
}

/**
 * @brief Returns the point where the ray hits the collider
 * @param type
 * @param collider
 * @return glm::vec3
 */
glm::vec3 Ray::GetRayHit(ColliderType type,Collider* collider) const
{
    if (type == ColliderType::BOX){
        auto* box = dynamic_cast<BoxCollider*>(collider);
        glm::vec3 min = box->center - box->size;
        glm::vec3 max = box->center + box->size;
        glm::vec3 tmin = (min - origin) / direction;
        glm::vec3 tmax = (max - origin) / direction;
        glm::vec3 real_min = glm::min(tmin, tmax);
        glm::vec3 real_max = glm::max(tmin, tmax);
        float min_max = glm::max(glm::max(real_min.x, real_min.y), real_min.z);
        float max_min = glm::min(glm::min(real_max.x, real_max.y), real_max.z);
        if (min_max <= max_min)
        {
            return origin + direction * min_max;
        }
    }
    else if(type == ColliderType::SPHERE)
    {
        auto *sphere = dynamic_cast<SphereCollider*>(collider);
        glm::vec3 oc = origin - sphere->center;
        float a = glm::dot(direction, direction);
        float b = 2.0f * glm::dot(oc, direction);
        float c = glm::dot(oc, oc) - sphere->radius * sphere->radius;
        float discriminant = b * b - 4 * a * c;
        if (discriminant > 0)
        {
            float t = (-b - sqrt(discriminant)) / (2.0f * a);
            return origin + direction * t;
        }
    
    }
}

/**
 * @brief Checks if the ray collides with the collider
 * @param collider
 * @return bool
 */
bool Ray::doesCollide(Collider* collider) const
{
    if(collider->type == ColliderType::BOX)
    {
        auto* box = dynamic_cast<BoxCollider*>(collider);
        glm::vec3 min = box->center - box->size;
        glm::vec3 max = box->center + box->size;
        glm::vec3 tmin = (min - origin) / direction;
        glm::vec3 tmax = (max - origin) / direction;
        glm::vec3 real_min = glm::min(tmin, tmax);
        glm::vec3 real_max = glm::max(tmin, tmax);
        float min_max = glm::max(glm::max(real_min.x, real_min.y), real_min.z);
        float max_min = glm::min(glm::min(real_max.x, real_max.y), real_max.z);
        if (min_max <= max_min)
        {
            return true;
        }
    }
    else if(collider->type == ColliderType::SPHERE)
    {
        auto *sphere = dynamic_cast<SphereCollider*>(collider);
        glm::vec3 oc = origin - sphere->center;
        float a = glm::dot(direction, direction);
        float b = 2.0f * glm::dot(oc, direction);
        float c = glm::dot(oc, oc) - sphere->radius * sphere->radius;
        float discriminant = b * b - 4 * a * c;
        if (discriminant > 0)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Returns the point where the ray hits the collider
 * @return glm::vec3
 */
glm::vec3 Ray::RayHitPoint() {
    return RayHit;
}





