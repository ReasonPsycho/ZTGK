#include "UnitAI.h"

UnitAI::UnitAI(Unit *pUnit, StateManager *pStateManager) {
    unit = pUnit;
    stateManager = pStateManager;

    unit->addComponent(std::unique_ptr<UnitAI>(this));

    stateManager->unit = unit;
    unit->currentState = stateManager->currentState;
}

UnitAI::~UnitAI() {
    delete unit;
    delete stateManager;
}

void UnitAI::Update() {
    stateManager->RunStateMachine();
    unit->currentState = stateManager->currentState;
}

void UnitAI::showImGuiDetails(Camera *camera) {

}
