#include "UnitAI.h"

UnitAI::UnitAI(Unit *pUnit, StateManager *pStateManager) {
    name = "Unit AI";
    unit = pUnit;
    stateManager = pStateManager;
    stateManager->unit = unit;
    unit->currentState = std::move(stateManager->currentState);
}

UnitAI::~UnitAI() {
    delete unit;
    delete stateManager;
}

void UnitAI::UpdateImpl() {
    stateManager->RunStateMachine();
    unit->currentState = std::move(stateManager->currentState);
}

void UnitAI::showImGuiDetailsImpl(Camera *camera) {

}
