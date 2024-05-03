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
#include "ECS/Render/WireRenderer.h"

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

void UnitSystem::showImGuiDetailsImpl(Camera *camera) {
    ImGui::Text("Units: %d", unitComponents.size());
    ImGui::Text("Selected Units: %d", selectedUnits.size());
}

void UnitSystem::UpdateImpl() {
    for (Unit* unit: unitComponents) {
        unit->UpdateImpl();
        unit->getEntity()->getComponent<UnitAI>()->UpdateImpl();
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
                        deselectAllUnits();
                    }

                    ztgk::game::scene->systemManager.getSystem<WireRenderer>()->rayComponents.push_back(std::move(ray));
                }
                else if (!selectedUnits.empty() && data.button == GLFW_MOUSE_BUTTON_RIGHT && data.action == GLFW_PRESS) {
                    glm::vec3 worldPressCoords = ztgk::game::camera->getDirFromCameraToCursor(data.pos.x - 10, data.pos.y - 10, ztgk::game::window_size.x, ztgk::game::window_size.y);
                    std::unique_ptr<Ray> ray = make_unique<Ray>(ztgk::game::camera->Position, worldPressCoords, ztgk::game::scene->systemManager.getSystem<CollisionSystem>());

                    Entity * hit = ray->getHitEntity();
                    if(hit != nullptr){
                        for(auto & unit : selectedUnits){
                            if(hit->getComponent<IMineable>()!=nullptr){
                                unit->miningTarget = hit->getComponent<IMineable>();
                                unit->hasMiningTarget = true;
                                spdlog::info("Mining target set at {}, {}", hit->getComponent<IMineable>()->gridPosition.x, hit->getComponent<IMineable>()->gridPosition.z);
                            }
                            else{
                                unit->hasMiningTarget = false;
                                unit->miningTarget = nullptr;
                                unit->hasCombatTarget = false;
                                unit->combatTarget = nullptr;
                                unit->hasMovementTarget = true;
                                unit->pathfinding.path.clear();
                                unit->movementTarget = ztgk::game::scene->systemManager.getSystem<Grid>()->WorldToGridPosition( VectorUtils::GlmVec3ToVector3(hit->transform.getGlobalPosition()));
                            }
                        }
                    }

                    ztgk::game::scene->systemManager.getSystem<WireRenderer>()->rayComponents.push_back(std::move(ray));
                }
            }
        }
    );
    *ztgk::game::signalQueue += raycastSelectionHandler.get();
}
