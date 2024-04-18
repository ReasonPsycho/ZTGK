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
    ImGui::Begin("Unit System");
    ImGui::Text("Units: %d", unitComponents.size());
    ImGui::Text("Selected Units: %d", selectedUnits.size());
    ImGui::End();
}

void UnitSystem::Update() {
    for (Unit* unit: unitComponents) {
        unit->Update();
        unit->getEntity()->getComponent<UnitAI>()->Update();
        unit->getEntity()->getComponent<BoxCollider>()->update();
    }
}

void UnitSystem::selectUnit(Unit *unit) {
    selectedUnits.push_back(unit);
    unit->isSelected = true;
}

void UnitSystem::deselectUnit(Unit *unit) {
    auto unit_iter = std::find(selectedUnits.begin(), selectedUnits.end(), unit);

    if (unit_iter != selectedUnits.end()) {
        selectedUnits.erase(unit_iter);
        unit->isSelected = false;
    }
}

void UnitSystem::deselectAllUnits() {
    for (Unit* unit: selectedUnits) {
        unit->isSelected = false;
    }
    selectedUnits.clear();
}
