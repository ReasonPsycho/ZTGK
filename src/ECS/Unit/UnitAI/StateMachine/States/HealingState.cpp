//
// Created by igork on 16.06.2024.
//

#include "HealingState.h"
#include "ECS/Unit/Unit.h"
#include "ECS/Unit/UnitAI/StateMachine/State.h"
#include "IdleState.h"
#include "ECS/Render/Components/ColorMask.h"
#include "ECS/Utils/Time.h"


HealingState::HealingState(Grid *grid, Unit* unit) {
    this->grid = grid;
    name = "Healing State";
    this->unit = unit;
    healingAmount = unit->stats.max_hp / 10;
}

State *HealingState::RunCurrentState() {
    unit->playinIdleAnimation = false;
    if (unit->stats.hp < unit->stats.max_hp) {
        HealSelf();
    } else {
        unit->isAlive = true;
        unit->isBeingHealedByWashingMachine = false;
        auto idleState = new IdleState(grid);
        idleState->unit = unit;
        return idleState;
    }
    return this;
}

bool HealingState::isTargetInRange() {
    return false;
}

void HealingState::HealSelf() {
   auto colorMask = unit->getEntity()->getComponent<ColorMask>();
    if (colorMask == nullptr) {
        unit->getEntity()->addComponent(std::make_unique<ColorMask>());
        colorMask = unit->getEntity()->getComponent<ColorMask>();
    }
    if(glfwGetTime() - lastHealingTime > healingCooldown){
       unit->stats.hp += healingAmount;
       lastHealingTime = glfwGetTime();
       colorMask->AddMask("Healing", glm::vec4(0, 255, 0, 255), 1);
       ztgk::game::audioManager->playRandomSoundFromGroup("heal");
   }
    else{
        auto value = colorMask->GetMaskColor("Healing").a - 255.f * 1.3*Time::Instance().DeltaTime();
        colorMask->ChangeMaskColor("Healing", glm::vec4(0, 1, 0, value <= 0 ? 0 : value));
    }


}
