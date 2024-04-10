//
// Created by redkc on 18/02/2024.
//
#include "Entity.h"
#include "Scene.h"
#include "../Raycasting/Collider.h"
#include "Raycasting/Colliders/BoxCollider.h"
#include "Raycasting/Colliders/SphereCollider.h"

void Scene::updateScene() {
    for (auto &&child: children) {
        child->updateSelfAndChild();
    }
}

Entity *Scene::addEntity(std::string name) {
    children.push_back(make_unique<Entity>(this, name));
    return children.back().get();
}
void Scene::removeChild(Entity *child) {
auto iter = std::find_if(children.begin(), children.end(),
                         [&](const std::unique_ptr<Entity>& e) { return e.get() == child; });
if (iter != children.end())
{
// Entity was found. Now remove it.
// unique_ptr will automatically delete the Entity when erased.
children.erase(iter);
}
}


Entity *Scene::addEntity(Entity *parent, std::string name) {
    return parent->addChild(make_unique<Entity>(this, parent, name));
}

void Scene::showImGuiDetails(Camera *camera) {
// Begin main window
    ImGui::SetNextWindowPos(ImVec2(40, 40), ImGuiCond_Once);
    ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking);

// Provide the 'dockspace' into which other ImGui windows can be docked
    ImGuiID dockspace_id = ImGui::GetID("Scene");
    ImGui::DockSpace(dockspace_id);

    ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
    ImGui::Begin("Scene graph");
    for (auto &child: children) {
        if(!stopRenderingImgui){
            child->showImGuiDetails(camera);
        }
    }
    ImGui::End();
    for (const auto &system: systemManager.systems) {
        ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
        ImGui::Begin(system.second->name.c_str());
        system.second->showImGuiDetails(camera);
        ImGui::End();
    }   
    ImGui::End();
    stopRenderingImgui = false;
}

std::vector<std::unique_ptr<Entity>> &Scene::getChildren() {
    return children;
}

void collectCollidersRecursive(Entity* entity, std::vector<Collider*>& colliders) {
    // Check if the entity has any collider components and add them to the colliders vector
    for (auto& componentPair : entity->components) {
        if (auto collider = dynamic_cast<Collider*>(componentPair.second.get())) {
            colliders.push_back(collider);
        }
    }

    // Recursively iterate over all children entities
    for (auto& child : entity->children) {
        collectCollidersRecursive(child.get(), colliders);
    }
}

std::vector<Collider*> Scene::getColliders() {
    std::vector<Collider*> colliders;

    // Iterate over all entities in the scene
    for (auto& entity : children) {
        // Recursively collect collider components from all children of the entity
        collectCollidersRecursive(entity.get(), colliders);
    }

    return colliders;
}
