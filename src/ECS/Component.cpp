//
// Created by redkc on 22/02/2024.
//
#include "Entity.h"
#include "Component.h"


int Component::nextID = 0;


Entity *Component::getEntity() {  // Function to set the parent entity
    return parentEntity;
}

Component::Component()  {
    uniqueID = nextID++; // Assign the current value of nextID and then increment it for the next instance
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
