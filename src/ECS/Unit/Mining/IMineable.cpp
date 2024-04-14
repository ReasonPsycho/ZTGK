//
// Created by igork on 24.03.2024.
//

#include "IMineable.h"

#include "ECS/SignalQueue/SignalReceiver.h"
#include "ECS/Utils/Time.h"

IMineable::IMineable(float timeToMine) {
    this->timeToMine = timeToMine;
    this->timeToMineRemaining = timeToMine;
}

void IMineable::Mine() {
    timeToMineRemaining -= Time::Instance().DeltaTime();
    if (timeToMineRemaining<=0) {
        delete this;
    }
}
