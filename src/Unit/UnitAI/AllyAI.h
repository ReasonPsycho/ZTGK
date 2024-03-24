//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_ALLYAI_H
#define ZTGK_ALLYAI_H


#include "ECS/Component.h"
#include "Unit/Unit.h"

class AllyAI : public Component{
public:
    AllyAI(Unit* pUnit, StateManager* pStateManager);
    ~AllyAI();

    void Update() override;

    private:
    Unit* unit;
    StateManager* stateManager;

};


#endif //ZTGK_ALLYAI_H
