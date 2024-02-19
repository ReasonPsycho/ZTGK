//
// Created by redkc on 10/01/2024.
//
#include "Enitity.h"



void Entity::drawSelfAndChild(Shader &ourShader) {
    draw(ourShader);

    for (auto &&child: children) {
        child->drawSelfAndChild(ourShader);
    }
}

void Entity::forceUpdateSelfAndChild() {
    if (parent)
        transform.computeModelMatrix(parent->transform.getModelMatrix());
    else
        transform.computeModelMatrix();

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


Entity::Entity(Entity *parent) : parent(parent){
    
    auto newEntity = std::make_shared<Entity>(*this);
    parent->addChild(newEntity);
    
}

void Entity::drawSelfAndChild(Shader &regularShader, Shader &instancedShader) {
   draw(regularShader,instancedShader);

    for (auto &&child: children) {
        child->drawSelfAndChild(regularShader,instancedShader);
    }
}
