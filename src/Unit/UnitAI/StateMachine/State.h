//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_STATE_H
#define ZTGK_STATE_H


#include "Unit/Unit.h"
#include "States/IdleState.h"
#include "States/CombatState.h"
#include "States/MiningState.h"
#include "States/MovementState.h"

class State {
public:
     Unit* unit;
     virtual State* RunCurrentState();
};


#endif //ZTGK_STATE_H
