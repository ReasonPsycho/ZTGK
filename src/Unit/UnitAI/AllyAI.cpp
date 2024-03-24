#include "AllyAI.h"

AllyAI::AllyAI(Unit *pUnit, StateManager *pStateManager) {
    unit = pUnit;
    stateManager = pStateManager;

    unit->addComponent(this);

    stateManager->unit = unit;
    unit->currentState = stateManager->currentState;
}

AllyAI::~AllyAI() {
    delete unit;
    delete stateManager;
}

void AllyAI::Update() {
    stateManager->RunStateMachine();
    unit->currentState = stateManager->currentState;
}
