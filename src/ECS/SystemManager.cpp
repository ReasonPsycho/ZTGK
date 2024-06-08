//
// Created by redkc on 23/02/2024.
//
#include "Entity.h"
#include "SystemManager.h"
#include "ECS/SaveSystem/LevelSaving.h"

void SystemManager::showImGuiDetails(Camera *camera) {
    ImGuiID dockspace_id = ImGui::GetID("Scene");

    
    
}

void SystemManager::showImGuiEnitityBar(Entity *entity) {
    if (ImGui::MenuItem("Add component")) {
        isAddComponentMenuOpen = true;
    }
    
    if (isAddComponentMenuOpen) {
        if (ImGui::Begin("Add component menu", &isAddComponentMenuOpen, ImGuiWindowFlags_AlwaysAutoResize)) {
            selectedEntity = entity;
            
            ImGui::Combo("Components", &selectedItem, cStringList.data(), cStringList.size());
            
            if(ImGui::Button("Add")){
         
            }
            ImGui::End();
        }

    }
}

void SystemManager::Update() {
    if(selectedItem != -1){
        selectedEntity->addComponent(std::move(componentFactories[componentKeys[selectedItem]]()));
        selectedEntity->scene->stopRenderingImgui = true;
        isAddComponentMenuOpen = false;
        selectedEntity = nullptr;
        selectedItem = -1;
    }
}

void SystemManager::FinishInnit() {
    componentNames.clear();
    componentKeys.clear();
    for (auto &component : componentFactories) {
        componentNames.push_back( component.first.name());
        componentKeys.push_back( component.first);
    }
    // Create the vector of C-style string pointers.
    for(const auto& str : componentNames)
        cStringList.push_back(str.c_str());

}

