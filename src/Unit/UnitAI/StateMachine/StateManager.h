#ifndef ZTGK_STATEMANAGER_H
#define ZTGK_STATEMANAGER_H

#include "State.h"
#include "ECS/Component.h"
class Unit;

class StateManager : public Component {
public:
    StateManager(Unit *pUnit);

    Unit* unit;

private:
    State* currentState;

    void RunStateMachine();
    void SwitchToTheNextState(State* nextState);
};

#endif //ZTGK_STATEMANAGER_H
