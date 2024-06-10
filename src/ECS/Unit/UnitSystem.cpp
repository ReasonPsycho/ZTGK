//
// Created by igork on 18.04.2024.
//

#include "UnitSystem.h"
#include "ECS/Unit/UnitAI/UnitAI.h"
#include "ECS/SignalQueue/Signal.h"
#include "ECS/SignalQueue/SignalQueue.h"
#include "ECS/SignalQueue/DataCargo/MouseEvents/MouseButtonSignalData.h"
#include "ECS/Raycasting/Ray.h"
#include "ECS/Utils/Globals.h"
#include "GLFW/glfw3.h"
#include "ECS/Render/WireRenderSystem.h"
#include "ECS/Utils/Time.h"
#include "ECS/Unit/Mining/PickupubleItem.h"
#include "ECS/Unit/Mining/MineableChest.h"

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
        spdlog::info("Component successfully removed {}.", typeid(*((Unit *)component)).name());
    } else {
        spdlog::warn("Attempted to remove a component that does not exist in the map: {}.", typeid(*((Unit *)component)).name());
    }
}

const std::type_index *UnitSystem::getComponentTypes() {
    return componentTypes.data();
}

void UnitSystem::showImGuiDetailsImpl(Camera *camera) {
    if (ImGui::CollapsingHeader(std::format("Units: {}###UnitSystem_Units", unitComponents.size()).c_str())) {
        for (auto & unit : unitComponents) {
            if (ImGui::TreeNode(std::format("{} - id {}", unit->name, unit->uniqueID).c_str())) {
                unit->showImGuiDetailsImpl(camera);
                ImGui::TreePop();
            }
        }
    }
    if (ImGui::CollapsingHeader(std::format("Units: {}###UnitSystem_SelectedUnits", selectedUnits.size()).c_str())) {
        for (auto & unit : selectedUnits) {
            if (ImGui::TreeNode(std::format("{} - id {}", unit->name, unit->uniqueID).c_str())) {
                unit->showImGuiDetailsImpl(camera);
                ImGui::TreePop();
            }
        }
    }

}

void UnitSystem::UpdateImpl() {
    for (Unit* unit: unitComponents) {
        if(std::find(unitComponents.begin(), unitComponents.end(), unit) == unitComponents.end()) continue;
        unit->UpdateImpl();
        unit->getEntity()->getComponent<UnitAI>()->Update();
        unit->getEntity()->getComponent<BoxCollider>()->Update();
        if(std::find(unitComponents.begin(), unitComponents.end(), unit) == unitComponents.end()) continue;

        //those find statements are needed because unit can be deleted in the UpdateImpl() function, which does not update unitComponents vector
    }

    float xd = glfwGetTime();
    int xdd = (int)xd;
    int xddd = xdd % 2;
    if((int)glfwGetTime() % 2 == 0){
        fixOverlappingUnits();
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

void UnitSystem::init() {
}

void UnitSystem::fixOverlappingUnits() {
    for (Unit* unit: unitComponents) {
        for (Unit* otherUnit: unitComponents) {
            if (unit != otherUnit && unit->gridPosition == otherUnit->gridPosition) {
                Vector2Int random_dir;
                switch((int)glfwGetTime()%4){
                    case 0:
                        random_dir = Vector2Int{1, 0};
                        break;
                    case 1:
                        random_dir = Vector2Int{-1, 0};
                        break;
                    case 2:
                        random_dir = Vector2Int{0, 1};
                        break;
                    case 3:
                        random_dir = Vector2Int{0, -1};
                        break;
                }
                unit->gridPosition = unit->pathfinding.GetNearestVacantTile(unit->gridPosition, otherUnit->gridPosition + random_dir);
            }
        }
    }
}
