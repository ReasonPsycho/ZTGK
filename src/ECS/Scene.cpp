//
// Created by redkc on 18/02/2024.
//
#include "Entity.h"
#include "Scene.h"
#include "../ECS/Raycasting/Collider.h"
#include "ECS/Raycasting/Colliders/BoxCollider.h"
#include "ECS/Raycasting/Colliders/SphereCollider.h"
#include "ECS/SaveSystem/LevelSaving.h"
#include "tracy/Tracy.hpp"

void Scene::updateScene() {
    ZoneScopedN("Update scene");


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
                             [&](const std::unique_ptr<Entity> &e) { return e.get() == child; });
 

    if (iter != children.end()) {
        // Entity was found. Now remove it.
        // unique_ptr will automatically delete the Entity when erased.
        children.erase(iter);
    }
    stopRenderingImgui = true;
}


Entity *Scene::addEntity(Entity *parent, std::string name) {
    return parent->addChild(make_unique<Entity>(this, parent, name));
}

void Scene::showImGuiDetails(Camera *camera) {
    ZoneScopedN("ShowImGuiDetails Scene");

// Begin main window
    ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking);
    if (ImGui::BeginMenuBar()) {
        if (ImGui::MenuItem("Add entity")) {
            addEntity("New entity");
        }
        if (ImGui::MenuItem("Save")) {
            LevelSaving::save();
        }
        if (ImGui::MenuItem("Load")) {
            LevelSaving::load();
        }
        
        ImGui::EndMenuBar();
    }

// Provide the 'dockspace' into which other ImGui windows can be docked
    ImGuiID dockspace_id = ImGui::GetID("Scene");
    ImGui::DockSpace(dockspace_id);

    ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
    ImGui::Begin("Scene graph");
    for (auto &child: children) {
        if (!stopRenderingImgui) {
            child->showImGuiDetails(camera);
        }
    }
    ImGui::End();
    auto &systems = systemManager.systems;
    for (const auto &system: systemManager.systems) {
        ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
        ImGui::Begin(system.second->name.c_str());
        system.second->showImGuiDetails(camera);
        ImGui::End();
    }
    stopRenderingImgui = false;
}

std::vector<std::unique_ptr<Entity>> &Scene::getChildren() {
    return children;
}

Entity *Scene::getChild(unsigned int id) const {
    auto found = std::find_if(children.begin(), children.end(), [id](auto & child){
        return child->uniqueID == id;
    });
    return found == children.end() ? nullptr : found->get();
}

Entity *Scene::getChild(const string &name) const {
    auto found = std::find_if(children.begin(), children.end(), [name](auto & child){
        return child->name == name;
    });
    return found == children.end() ? nullptr : found->get();
}

Entity *Scene::getChildR(unsigned int id) const {
    Entity * found = getChild(id);
    if (found != nullptr)
        return found;

    for (auto & child : children) {
        found = child->getChildR(id);
        if (found != nullptr)
            return found;
    }
    return nullptr;
}

Entity *Scene::getChildR(const string &name) const {
    Entity * found = getChild(name);
    if (found != nullptr)
        return found;

    for (auto & child : children) {
        found = child->getChildR(name);
        if (found != nullptr)
            return found;
    }
    return nullptr;
}

