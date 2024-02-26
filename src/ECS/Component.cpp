//
// Created by redkc on 22/02/2024.
//
#include "Entity.h"
#include "Component.h"

Entity *Component::getEntity() {  // Function to set the parent entity
    return parentEntity;
}

Component::Component()  {

}

void Component::setIsDirty(bool dirtValue) {
    isDirty = dirtValue;
}

bool Component::getIsDirty() {
    return isDirty;
}

void Component::setEntity(Entity *newParentEntity) {
parentEntity = newParentEntity;
}
