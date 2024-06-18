//
// Created by igork on 16.06.2024.
//

#ifndef ZTGK_HEALINGSTATE_H
#define ZTGK_HEALINGSTATE_H
#include "ECS/Unit/UnitAI/StateMachine/State.h"

class HealingState : public State{
public:
    HealingState(Grid* grid, Unit* unit);

    State* RunCurrentState() override;
    bool isTargetInRange() override;

    void HealSelf();

private:
    double healingCooldown = 1;
    double lastHealingTime = 0;
    double healingAmount;
};


#endif //ZTGK_HEALINGSTATE_H
