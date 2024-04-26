//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_STATE_H
#define ZTGK_STATE_H


#include "ECS/Grid/Grid.h"

class Unit;

class State {
public:
    virtual ~State() = default;

     Unit* unit;
     Grid* grid;
     virtual State* RunCurrentState() = 0;
     virtual bool isTargetInRange() = 0;
};


#endif //ZTGK_STATE_H
