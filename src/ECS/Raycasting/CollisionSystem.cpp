//
// Created by igork on 16.04.2024.
//

#include <ranges>
#include "CollisionSystem.h"
#include "imgui.h"
#include "ECS/Utils/VectorUtils.h"


void CollisionSystem::addComponent(void *component) {
    Component* basePtr = static_cast<Component*>(component);

    BoxCollider* boxPtr = dynamic_cast<BoxCollider*>(basePtr);
    if(boxPtr != nullptr)
    {
        if (boxPtr->collisionType != TILE){
            BoxColliders.push_back(boxPtr);
        }
    }

    SphereCollider* spherePtr = dynamic_cast<SphereCollider*>(basePtr);

    if(spherePtr != nullptr)
    {
        SphereColliders.push_back(spherePtr);
    }
}

void CollisionSystem::removeComponent(void *component) {


    auto box_iter = std::find(BoxColliders.begin(), BoxColliders.end(), reinterpret_cast<BoxCollider *const>(component));

    if (box_iter != BoxColliders.end()) {
        BoxColliders.erase(box_iter);
        return;
    }

    
    auto sphere_iter = std::find(SphereColliders.begin(), SphereColliders.end(), reinterpret_cast<SphereCollider *const>(component));

    if (sphere_iter != SphereColliders.end()) {
        SphereColliders.erase(sphere_iter);
        return;
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
    for (auto&  box : BoxColliders) {
        colliders.push_back(box);

    }
    for (auto&  sphere : SphereColliders) {
        colliders.push_back(sphere);
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
                                                                                // 2      4
    glm::vec3 p3 = glm::vec3(p2.x, y, p1.z);
    glm::vec3 p4 = glm::vec3(p1.x, y, p2.z);

    spdlog::info("p1: {} {} {}, p2: {} {} {}, p3: {} {} {}, p4: {} {} {}", p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z, p4.x, p4.y, p4.z);


    for(auto box : BoxColliders)
    {
 
            if(box->intersects(p1, p2, p3, p4))
            {
                colliders.push_back(box);
            }
        
    }

    return colliders;


}

void CollisionSystem::UpdateImpl() {
    for(auto& box : BoxColliders)
    {
        if(box->getIsDirty())
        {
            box->Update();
        }
    }
    for(auto& sphere : SphereColliders)
    {
        if(sphere->getIsDirty())
        {
            sphere->Update();
        }
    }
}
