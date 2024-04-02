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
    void showImGuiDetails(Camera *camera) override; // Pure virtual function

    
    private:
    Unit* unit;
    StateManager* stateManager;

};


#endif //ZTGK_ALLYAI_H
