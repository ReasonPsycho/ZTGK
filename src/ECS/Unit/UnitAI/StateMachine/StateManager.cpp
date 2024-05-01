//
// Created by igork on 22.03.2024.
//

#include "StateManager.h"
#include "State.h"

StateManager::StateManager(Unit *unit) {
    this->unit = unit;
    currentState = nullptr;

}

void StateManager::RunStateMachine() {
    if (currentState != nullptr) {
        State *nextState = currentState->RunCurrentState();
        if (nextState != nullptr) {
            SwitchToTheNextState(nextState);
        }
    }

}

void StateManager::SwitchToTheNextState(State *nextState) {
    currentState = nextState;
}


