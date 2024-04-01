//
// Created by redkc on 10/01/2024.
//

#include "Entity.h"


int Entity::nextID = 0;

Entity::Entity(Scene* scene, std::string name): scene(scene) , name(name){
    uniqueID = nextID++; // Assign the current value of nextID and then increment it for the next instance
}

Entity::Entity(Scene *scene, Entity *parent, std::string name): scene(scene),parent(parent) , name(name) {
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
    ImGuiStorage* storage = ImGui::GetStateStorage();

    if (ImGui::TreeNode(name.c_str())) {
        if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
            if (uniqueID != scene->selectedEntityNumber){
                storage->SetBool(scene->selectedEntityNumber, false); // close the tree node
                scene->selectedEntityNumber = uniqueID;
                storage->SetBool(uniqueID, true); // close the tree node
            }else{
                storage->SetBool(scene->selectedEntityNumber, false); // close the tree node
                scene->selectedEntityNumber = -1;
            }

        }
        
        if ( scene->selectedEntityNumber == uniqueID){
            ImVec2 window_pos = ImVec2(ImGui::GetIO().DisplaySize.x - 300, 40); // Top-Right
            ImGui::SetNextWindowPos(window_pos, ImGuiCond_FirstUseEver);
            ImGui::Begin( (name + ", Element id:" + std::to_string(uniqueID)).c_str());
            transform.ManipulateModelMatrix(camera);
            
            for (const auto &component: components) {
                component.second->showImGuiDetails(camera);
            }
            ImGui::End();
        }
        for (const auto &child: children) {
            child->showImGuiDetails(camera);
        }
        ImGui::TreePop();
    }
  
    ImGui::PopID();
}

Entity::~Entity() {

}



