//
// Created by igork on 16.04.2024.
//

#include "CollisionSystem.h"
#include "imgui.h"




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
