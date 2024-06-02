#ifndef ZTGK_STATEMANAGER_H
#define ZTGK_STATEMANAGER_H

#include "State.h"
#include "ECS/Component.h"
class Unit;

class StateManager{
public:
    StateManager(Unit *pUnit);

    Unit* unit;
    unique_ptr<State> currentState;
    void RunStateMachine();
private:
    void SwitchToTheNextState(std::unique_ptr<State> nextState);
};

#endif //ZTGK_STATEMANAGER_H
