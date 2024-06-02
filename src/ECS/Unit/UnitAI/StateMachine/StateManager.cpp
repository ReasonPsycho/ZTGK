//
// Created by igork on 22.03.2024.
//

#include "StateManager.h"
#include "State.h"
#include "ECS/Utils/Globals.h"
#include "ECS/Unit/UnitAI/StateMachine/States/IdleState.h"

StateManager::StateManager(Unit *unit) {
    this->unit = unit;
    currentState = nullptr;

}

void StateManager::RunStateMachine() {
    if(currentState == nullptr) {
        currentState = std::move(IdleState::getInstance(ztgk::game::scene->systemManager.getSystem<Grid>() ,unit));
    }
    if (currentState != nullptr) {
        std::unique_ptr<State> nextState = currentState->RunCurrentState();
        if (nextState != nullptr) {
            SwitchToTheNextState(std::move(nextState));
        }
    }

}

void StateManager::SwitchToTheNextState(std::unique_ptr<State> nextState) {
    currentState = std::move(nextState);
}


