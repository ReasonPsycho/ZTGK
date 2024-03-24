//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_ALLYAI_H
#define ZTGK_ALLYAI_H


#include "ECS/Component.h"
#include "Unit/Unit.h"

class UnitAI : public Component{
public:
    UnitAI(Unit* pUnit, StateManager* pStateManager);
    ~UnitAI();

    void Update() override;

    private:
    Unit* unit;
    StateManager* stateManager;

};


#endif //ZTGK_ALLYAI_H
