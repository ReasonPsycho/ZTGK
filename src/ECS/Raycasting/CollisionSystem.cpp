//
// Created by igork on 16.04.2024.
//

#include "CollisionSystem.h"
#include "imgui.h"
#include "ECS/Utils/VectorUtils.h"


void CollisionSystem::addComponent(void *component) {
    auto c =(Collider*)component;
    if (c->type == ColliderType::BOX) {
        auto* boxCollider = static_cast<BoxCollider*>(component);
        BoxColliders[boxCollider->uniqueID].push_back(boxCollider);
    } else if (c->type == ColliderType::SPHERE) {
        auto* sphereCollider = static_cast<SphereCollider*>(component);
        SphereColliders[sphereCollider->uniqueID].push_back(sphereCollider);
    }
}

void CollisionSystem::removeComponent(void *component) {
    auto c =(Collider*)component;
    if (c->type == ColliderType::BOX) {
        erase(BoxColliders[c->uniqueID], dynamic_cast<BoxCollider*>(c));
    } else if (c->type == ColliderType::SPHERE) {
        erase(SphereColliders[c->uniqueID], dynamic_cast<SphereCollider*>(c));
    }
}

const std::type_index* CollisionSystem::getComponentTypes() {
    return componentTypes.data();
}

int CollisionSystem::getNumComponentTypes() {
    return componentTypes.size();
}

void CollisionSystem::showImGuiDetailsImpl(Camera *camera) {

    ImGui::Begin("Collision System");
    ImGui::Text("Box Colliders: %zu", BoxColliders.size());
    ImGui::Text("Sphere Colliders: %zu", SphereColliders.size());
    ImGui::End();
}

std::vector<Collider *> CollisionSystem::getColliders() {
    std::vector<Collider *> colliders;
    for (auto& [id, boxes] : BoxColliders) {
        for (auto& box : boxes) {
            colliders.push_back(box);
        }
    }
    for (auto& [id, spheres] : SphereColliders) {
        for (auto& sphere : spheres) {
            colliders.push_back(sphere);
        }
    }
    return colliders;
}

CollisionSystem::CollisionSystem() {
    name = "Collision System";
}

std::vector<Collider *> CollisionSystem::getCollidersInArea(glm::vec3 p1, glm::vec3 p2) {
    std::vector<Collider*> colliders;

    //calculate the bounding box                                                // 1      3
                                                                                //
    float y = p1.y;                                                             //
    glm::vec3 diagonal = p2 - p1;
    glm::vec3 p3 = p1;
    glm::vec3 p4 = p1;                                                                       // 4      2
    if(diagonal == glm::vec3(0.0f, 0.0f, 0.0f)){
        p3 = p1;
        p4 = p1;
    }
    else {
        glm::vec3 unitDiagonal = glm::normalize(diagonal);
        glm::vec3 normal(0.0f, 1.0f, 0.0f);
        glm::vec3 parallel = glm::cross(normal, unitDiagonal);

        p3 = p1 + parallel;
        p4 = p2 + parallel;
    }
    spdlog::info("p1: {} {} {}, p2: {} {} {}, p3: {} {} {}, p4: {} {} {}", p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z, p4.x, p4.y, p4.z);


    for(auto collider : BoxColliders)
    {
        for(auto box : collider.second)
        {
            if(box->intersects(p1, p2, p3, p4))
            {
                colliders.push_back(box);
            }
        }
    }

    return colliders;


}
