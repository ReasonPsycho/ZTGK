//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_MOVEMENTSTATE_H
#define ZTGK_MOVEMENTSTATE_H
#include "../State.h"
#include "CombatState.h"


class MovementState : public State{

public:
    State* RunCurrentState() override;

    CombatState* CombatState;
    bool hasCombatTarget;
    bool isAttackTargetInRange;
};


#endif //ZTGK_MOVEMENTSTATE_H
