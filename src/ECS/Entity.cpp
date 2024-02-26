//
// Created by redkc on 10/01/2024.
//
#include "Entity.h"


Entity::Entity(SystemManager *systemManager): systemManager(systemManager) {

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

