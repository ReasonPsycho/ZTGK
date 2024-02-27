//
// Created by redkc on 10/01/2024.
//
#include "Entity.h"

int Entity::nextID = 0;

Entity::Entity(SystemManager *systemManager, string name): systemManager(systemManager) , name(name){
    uniqueID = nextID++; // Assign the current value of nextID and then increment it for the next instance
}



void Entity::forceUpdateSelfAndChild() {
    if (parent)
        transform.computeModelMatrix(parent->transform.getModelMatrix());
    else
        transform.computeModelMatrix();
    
    for(auto& pair : components) {
        pair.second->setIsDirty(true);
    }    
    
    for (auto &&child: children) {
        child->forceUpdateSelfAndChild();
    }
}

void Entity::updateSelfAndChild() {
    if (transform.isDirty()) {
        forceUpdateSelfAndChild();
        return;
    }else{
        for(auto& pair : components) {
            pair.second->setIsDirty(false);
        }      
    }
    
    for (auto &&child: children) {
        child->updateSelfAndChild();
    }
}

Entity* Entity::addChild(std::unique_ptr<Entity> child) {
    child->parent = this;
    children.push_back(std::move(child));
    return children.back().get();
}

void Entity::showImGuiDetails(Camera *camera) {
    ImGui::PushID(uniqueID);
    
    if (ImGui::TreeNode(name.c_str())) {
        if (ImGui::IsItemClicked()  && !ImGui::IsItemToggledOpen()) {
            isSelected = !isSelected;
        }
        if (isSelected){
            ImGui::Begin(name.c_str());
            transform.ManipulateModelMatrix(camera);
            ImGui::End();
        }
        for (const auto &child: children) {
            child->showImGuiDetails(camera);
        }
        ImGui::TreePop();
    }
  
    ImGui::PopID();
}


