//
// Created by redkc on 22/02/2024.
//
#include "Entity.h"
#include "Component.h"
#include "Utils/Util.h"

using namespace ztgk;


Entity *Component::getEntity() {  // Function to set the parent entity
    return parentEntity;
}

Component::Component() : uniqueID(id<ID_POOL_COMPONENT>())  {}

void Component::setIsDirty(bool dirtValue) {
    isDirty = dirtValue;
}

bool Component::getIsDirty() {
    return isDirty;
}

void Component::setEntity(Entity *newParentEntity) {
parentEntity = newParentEntity;
}

void Component::showImGuiDetails(Camera *camera) {
    ZoneTransientN(zoneName,(name).c_str(),true);
    showImGuiDetailsImpl(camera);
}

void Component::Update() {
    ZoneTransientN(zoneName,(name).c_str(),true);
    UpdateImpl();
}

void Component::Remove() {
    parentEntity->removeComponentFromMap(this);
}
