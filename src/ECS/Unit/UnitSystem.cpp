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
    raycastSelectionHandler = std::make_unique<SignalReceiver>(
        Signal::signal_types.mouse_move_signal | Signal::signal_types.mouse_button_signal,
        [this](const Signal & signal) {
            if (signal.stype == Signal::signal_types.mouse_move_signal) {
                // todo cast ray for hover highlight
            } else if (signal.stype == Signal::signal_types.mouse_button_signal) {
                auto data = *dynamic_pointer_cast<MouseButtonSignalData>(signal.data);

                if (data.button == GLFW_MOUSE_BUTTON_LEFT && data.action == GLFW_PRESS) {
                    glm::vec3 worldPressCoords = ztgk::game::camera->getDirFromCameraToCursor(data.pos.x - 10, data.pos.y - 10, ztgk::game::window_size.x, ztgk::game::window_size.y);
                    std::unique_ptr<Ray> ray = make_unique<Ray>(ztgk::game::camera->Position, worldPressCoords, ztgk::game::scene->systemManager.getSystem<CollisionSystem>());

                    if (ray->getHitEntity() != nullptr && ray->getHitEntity()->getComponent<Unit>() != nullptr && ray->getHitEntity()->getComponent<Unit>()->isAlly){
                        if (ray->getHitEntity()->getComponent<Unit>()->isSelected) {
                            deselectUnit(ray->getHitEntity()->getComponent<Unit>() );
                        } else {
                            selectUnit(ray->getHitEntity()->getComponent<Unit>());
                        }
                    } else if(ray->getHitEntity() != nullptr && ray->getHitEntity()->getComponent<Unit>() == nullptr){
                        //deselectAllUnits();
                    }

                    ztgk::game::scene->systemManager.getSystem<WireRenderSystem>()->rayComponents.push_back(std::move(ray));
                }
                else if (!selectedUnits.empty() && data.button == GLFW_MOUSE_BUTTON_RIGHT && data.action == GLFW_PRESS) {
                    glm::vec3 worldPressCoords = ztgk::game::camera->getDirFromCameraToCursor(data.pos.x - 10, data.pos.y - 10, ztgk::game::window_size.x, ztgk::game::window_size.y);
                    std::unique_ptr<Ray> ray = make_unique<Ray>(ztgk::game::camera->Position, worldPressCoords, ztgk::game::scene->systemManager.getSystem<CollisionSystem>());

                    Entity * hit = ray->getHitEntity();
                    if(hit != nullptr){
                        for(auto & unit : selectedUnits){
                            auto atktarget = hit->getComponent<Unit>();
                            auto pItem = hit->getComponent<PickupubleItem>();
                            if (atktarget != nullptr && atktarget != unit) {
                                spdlog::info("set combat target for {} to {}", unit->name, atktarget->name);
                                unit->hasCombatTarget = true;
                                unit->combatTarget = hit->getComponent<Unit>();
                            }
                            if (pItem != nullptr) {
                                auto pos = pItem->getEntity()->transform.getGlobalPosition();
                                spdlog::info("set pickup target");
                                unit->pickupTarget = pItem;
                                unit->hasPickupTarget = true;
                                unit->hasMovementTarget = true;
                                unit->movementTarget = unit->grid->WorldToGridPosition({pos.x, pos.y, pos.z});
                            }
                            if(hit->getComponent<IMineable>()!=nullptr){
                                unit->miningTargets.clear();
                                unit->miningTargets.push_back(hit->getComponent<IMineable>());
                                unit->hasMiningTarget = true;
                                spdlog::info("Mining target set at {}, {}", hit->getComponent<IMineable>()->gridPosition.x, hit->getComponent<IMineable>()->gridPosition.z);
                            }
                            if(hit->getComponent<MineableChest>()!=nullptr){
                                unit->miningTargets.clear();
                                unit->miningTargets.push_back(hit->getComponent<MineableChest>());
                                unit->hasMiningTarget = true;
                                spdlog::info("Mining target set at {}, {}", hit->getComponent<MineableChest>()->gridPosition.x, hit->getComponent<MineableChest>()->gridPosition.z);
                            }
                            else{
                                unit->hasMiningTarget = false;
                                spdlog::info("Mining target not set");
                                unit->miningTargets.clear();
                                unit->hasCombatTarget = false;
                                unit->combatTarget = nullptr;
                                unit->hasMovementTarget = true;
                                unit->pathfinding.path.clear();
                                unit->movementTarget = ztgk::game::scene->systemManager.getSystem<Grid>()->WorldToGridPosition( VectorUtils::GlmVec3ToVector3(hit->transform.getGlobalPosition()));
                            }
                        }
                    }

                    ztgk::game::scene->systemManager.getSystem<WireRenderSystem>()->rayComponents.push_back(std::move(ray));
                }
            }
        }
    );
    *ztgk::game::signalQueue += raycastSelectionHandler.get();
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
