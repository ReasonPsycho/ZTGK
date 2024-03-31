//
// Created by redkc on 18/02/2024.
//
#include "Entity.h"
#include "Scene.h"

void Scene::updateScene() {
    for (auto &&child: children) {
        child->updateSelfAndChild();
    }
}

Entity *Scene::addEntity(std::string name) {
    children.push_back(make_unique<Entity>(this, name));
    return children.back().get();
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
        child->showImGuiDetails(camera);
    }
    ImGui::End();
    for (const auto &system: systemManager.systems) {
        ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
        ImGui::Begin(system.second->name.c_str());
        system.second->showImGuiDetails(camera);
        ImGui::End();
    }   
    ImGui::End();
}
