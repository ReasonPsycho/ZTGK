//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_STATEMANAGER_H
#define ZTGK_STATEMANAGER_H
#include "State.h"

class StateManager {

private:
    State* currentState;

    void RunStateMachine();
    void SwitchToTheNextState(State* nextState);
};


#endif //ZTGK_STATEMANAGER_H
