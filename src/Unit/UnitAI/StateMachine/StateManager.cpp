//
// Created by igork on 22.03.2024.
//

#include "StateManager.h"

//This should be in an Update function
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