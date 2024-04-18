//
// Created by igork on 18.04.2024.
//

#include "UnitSystem.h"
#include "ECS/Unit/UnitAI/UnitAI.h"

UnitSystem::UnitSystem() {
    name = "UnitSystem";
}

void UnitSystem::addComponent(void *component) {
    unitComponents.push_back((Unit *)component);
}

void UnitSystem::removeComponent(void *component) {
    auto component_iter = std::find(unitComponents.begin(), unitComponents.end(), (Unit *)component);

    if (component_iter != unitComponents.end()) {
        unitComponents.erase(component_iter);
    }
}

const std::type_index *UnitSystem::getComponentTypes() {
    return componentTypes.data();
}

void UnitSystem::showImGuiDetails(Camera *camera) {

}

void UnitSystem::Update() {
    for (Unit* unit: unitComponents) {
        unit->Update();
        unit->getEntity()->getComponent<UnitAI>()->Update();
        unit->getEntity()->getComponent<BoxCollider>()->update();
    }
}
