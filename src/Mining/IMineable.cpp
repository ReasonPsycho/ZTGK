//
// Created by igork on 24.03.2024.
//

#include "IMineable.h"

IMineable::IMineable(float timeToMine) {
    this->timeToMine = timeToMine;
    this->timeToMineRemaining = timeToMine;
}

void IMineable::Mine() {
    //TODO: time delta time or something
    if (timeToMineRemaining<=0) {
        delete this;
    }
}
