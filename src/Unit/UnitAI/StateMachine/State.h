//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_STATE_H
#define ZTGK_STATE_H


class Unit;

class State {
public:

     Unit* unit;
     virtual State* RunCurrentState() = 0;
     virtual bool isTargetInRange() = 0;
};


#endif //ZTGK_STATE_H
