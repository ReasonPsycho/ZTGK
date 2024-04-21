//
// Created by redkc on 10/01/2024.
//

#include "Entity.h"
#include "Utils/Util.h"
using namespace ztgk;

Entity::Entity(Scene* scene, std::string name): uniqueID(id<ID_POOL_ENTITY>()), scene(scene) , name(name) {}

Entity::Entity(Scene *scene, Entity *parent, std::string name): uniqueID(id<ID_POOL_ENTITY>()), scene(scene), parent(parent) , name(name) {}


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

void Entity::removeComponentFromMap(const std::unique_ptr<Component>& comp) {
    std::type_index typeName = std::type_index(typeid(*comp));
    scene->systemManager.removeComponent(comp.get());
    components.erase(typeName);
}

Entity* Entity::addChild(std::unique_ptr<Entity> child) {
    child->parent = this;
    children.push_back(std::move(child));
    return children.back().get();
}

void Entity::removeChild(Entity *child) {
    std::erase_if(children, [&](const std::unique_ptr<Entity>& e) { return e->uniqueID == child->uniqueID; });
//    
//    auto iter = std::find_if(children.begin(), children.end(),
//                             [&](const std::unique_ptr<Entity>& e) { return e.get() == child; });
//    if (iter <= children.end())
//    {
//        // Entity was found. Now remove it.
//        // unique_ptr will automatically delete the Entity when erased.
//        children.erase(iter);
//    }
}

void Entity::showImGuiDetails(Camera *camera) {
    Component* componentToDelete = nullptr;
    ImGui::PushID(uniqueID);
    ImGuiStorage* storage = ImGui::GetStateStorage();

    if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_SpanAvailWidth)) {
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
                if (ImGui::CollapsingHeader(component.second->name.c_str())){
                    ImGui::Indent();
                    component.second->showImGuiDetails(camera);
                    if (ImGui::Button("Delete component")) {
                        scene->stopRenderingImgui = true; //Just in case I am not sure if needed here.
                        removeComponentFromMap(component.second);
                        break;
                    }
                    ImGui::Unindent();
                }
            }
            
            if (ImGui::Button("Delete entity")) {
                scene->stopRenderingImgui = true;
                Destroy();
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
    while (!components.empty()) {
        removeComponentFromMap(components.begin()->second);
    }
}

void Entity::Destroy() {
    if (parent != nullptr){
        parent->removeChild(this);
    }else{
        scene->removeChild(this);
    }
}



