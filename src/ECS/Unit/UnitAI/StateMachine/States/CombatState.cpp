//
// Created by igork on 22.03.2024.
//


#include "CombatState.h"
#include "ECS/Unit/Unit.h"
#include "ECS/Unit/UnitAI/StateMachine/State.h"
#include "MovementState.h"
#include "MiningState.h"
#include "IdleState.h"
#include "ECS/Utils/Globals.h"
#include "ECS/HUD/Interactables/HUDSlider.h"
#include "ECS/Render/Components/ColorMask.h"
#include "HealingState.h"
#include "ECS/Gameplay/WashingMachineTile.h"
#include "ECS/Unit/Equipment/Projectile/Projectile.h"

State *CombatState::RunCurrentState() {

    if(!unit->isAlive && unit->isAlly){
        auto neighs = grid->GetNeighbours(unit->gridPosition);
        for(auto n : neighs){
            if(n->getEntity()->getComponent<WashingMachineTile>() != nullptr){
                auto healingState = new HealingState(grid, unit);
                return healingState;
            }
        }
        auto moveState = new MovementState(grid);
        moveState->unit = unit;
        moveState->unit->movementTarget = unit->pathfinding.GetNearestVacantTile(unit->getClosestWashingMachineTile(), unit->gridPosition);
        return moveState;
    }

    //from Combat to Idle
    if (!unit->hasMovementTarget && !unit->hasCombatTarget && !unit->hasMiningTarget) {
        idleState = new IdleState(grid);
        idleState->unit = unit;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(1.5, 5.0);
        double random_number = dis(gen);

        idleState->randomTime = random_number;

        return idleState;
    }

    //from Combat to Movement
    if (unit->hasMovementTarget) {
        moveState = new MovementState(grid);
        moveState->unit = unit;

        return moveState;
    }

    //from Combat to Mining
    if (unit->hasMiningTarget) {
        miningState = new MiningState(grid);
        miningState->unit = unit;

        if(miningState->isTargetInRange())
            return miningState;
        else
        {
            unit->hasMovementTarget = true;
            auto closestMineable = unit->findClosestMineable();
            if (closestMineable != nullptr) {
                unit->movementTarget = closestMineable->gridPosition;
                moveState = new MovementState(grid);
                moveState->unit = unit;
                return moveState;
            }
            else
                return this;
        }
    }
    AttackTarget();
    return this;
}

bool CombatState::isTargetInRange() {
    if (unit->combatTarget == nullptr) {
        unit->hasCombatTarget = false;
        return false;
    }
        Unit *targ = unit->GetClosestEnemyInWeaponRange();
        if (targ == nullptr) {
            return false;
        }
        unit->combatTarget = targ;
        unit->isTargetInRange = true;
        return true;


}

void CombatState::AttackTarget() {

    if(isAttackOnCooldown()) return;

    if (unit-> combatTarget == nullptr) {
        unit->hasCombatTarget = false;
        return;
    }
    if(!unit->isTargetInRange){
        unit->hasMovementTarget = true;
        unit->movementTarget = unit->combatTarget->gridPosition;
        return;
    }
    float angle = atan2(unit->combatTarget->worldPosition.x - unit->worldPosition.x, unit->combatTarget->worldPosition.z - unit->worldPosition.z);
    unit->rotation = angle;

    auto target = unit->combatTarget;
    if(target == nullptr) return; //todo expand on this

    float totalAttackDamage =
            (useItem->stats.dmg + useItem->stats.dmg * unit->stats.added.dmg_perc + unit->stats.added.dmg_flat)
            * (1 - target->stats.added.def_perc) - target->stats.added.def_flat;

    useItem->cd_sec = useItem->stats.cd_max_sec;
    unit->equipment.cd_between_sec = unit->equipment.cd_between_max_sec;
    if(useItem->stats.range.add > 1){
        auto projectileEntity = ztgk::game::scene->addEntity("Projectile");
        projectileEntity->transform.setLocalPosition(unit->worldPosition);
        projectileEntity->addComponent(std::make_unique<Render>(ztgk::game::projectileModel));
        projectileEntity->addComponent(std::make_unique<Projectile>(unit->worldPosition,  target->worldPosition,unit, target, totalAttackDamage));
        projectileEntity->transform.setLocalScale({0.1f, 0.1f, 0.1f});
        projectileEntity->updateSelfAndChild();
    }
    else{
        applyDamage(unit, target, totalAttackDamage);
    }

}

 void CombatState::applyDamage(Unit *unit, Unit* target, float damage) {
    target->stats.hp -= damage;
    ColorMask* cm;
    if(target!= nullptr && target->getEntity() != nullptr)
        cm = target->getEntity()->getComponent<ColorMask>();
    else{
        unit->hasCombatTarget = false;
        unit->combatTarget = nullptr;
        return;
    }
    if (cm == nullptr){
        target->getEntity()->addComponent(std::make_unique<ColorMask>());
        cm = target->getEntity()->getComponent<ColorMask>();
    }
    cm->AddMask("DMG_taken", {120.0f/250.0f, 0, 0, 0.5f}, 0.6f);
    if (ztgk::game::ui_data.tracked_unit_id == target->uniqueID) {
        ztgk::game::scene->getChild("HUD")->getChild("Game")->getChild("Unit Details")->getChild("Display Bar")->getComponent<HUDSlider>()->displayMax = target->stats.max_hp + target->stats.added.max_hp;
        ztgk::game::scene->getChild("HUD")->getChild("Game")->getChild("Unit Details")->getChild("Display Bar")->getComponent<HUDSlider>()->set_in_display_range(target->stats.hp);
    }


    ztgk::game::audioManager->playRandomSoundFromGroup("punch");


    if(target->stats.hp <= 0){
        ztgk::game::audioManager->playRandomSoundFromGroup(target->isAlly ? "deathSponge" : "deathEnemy");

        unit->hasCombatTarget = false;
        target->isAlive = false;
        unit->combatTarget = nullptr;

        if(!target->isAlly)
            target->DIEXD();
        else{
            target->hasCombatTarget = false;
            target->combatTarget = nullptr;
            target->currentMiningTarget = nullptr;
            target->hasMiningTarget = false;
            target->miningTargets.clear();
            target->hasMovementTarget = false;
        }
    }
}


CombatState::CombatState(Grid *grid) {
    this->grid = grid;
    name = "Combat";
}

bool CombatState::isAttackOnCooldown() {
    if (unit->equipment.cd_between_sec > 0)
        return true;

    if (unit->equipment.use_default()) {
        if (unit->equipment.item0->cd_sec <= 0) {
            useItem = unit->equipment.item0;
            return false;
        }
        return true;
    }

    Item * it = nullptr;
    Item * sec_it = nullptr;
    glm::ivec2 pos = {unit->gridPosition.x, unit->gridPosition.z};
    glm::ivec2 tpos = {unit->combatTarget->gridPosition.x, unit->combatTarget->gridPosition.z};

    // sort by shorter range, with target within range
    // since use_default() returns false, either of the items is not null and offensive
    if (unit->equipment.item1 == nullptr && unit->equipment.rangeEff2.is_in_range(pos, tpos))
        it = unit->equipment.item2;
    else if (unit->equipment.item2 == nullptr && unit->equipment.rangeEff1.is_in_range(pos, tpos))
        it = unit->equipment.item1;
    else {
        // both are offensive items
        if (unit->equipment.item1->offensive && unit->equipment.item2->offensive) {
            bool in_range_1 = unit->equipment.rangeEff1.is_in_range(pos, tpos);
            bool in_range_2 = unit->equipment.rangeEff2.is_in_range(pos, tpos);

            // in range of both
            if (in_range_1 && in_range_2) {
                // set by shorter range
                if (unit->equipment.rangeEff1.add <= unit->equipment.rangeEff2.add) {
                    it = unit->equipment.item1; sec_it = unit->equipment.item2;
                } else {
                    it = unit->equipment.item2; sec_it = unit->equipment.item1;
                }
            // set the one that's in range
            } else if (in_range_1) {
                it = unit->equipment.item1;
            } else {
                it = unit->equipment.item2;
            }
        // set the one that's in range
        } else {
            if (unit->equipment.item1->offensive && unit->equipment.rangeEff1.is_in_range(pos, tpos))
                it = unit->equipment.item1;
            else if (unit->equipment.item2->offensive && unit->equipment.rangeEff2.is_in_range(pos, tpos))
                it = unit->equipment.item2;
        }
    }

    if (it != nullptr && it->cd_sec <= 0) {
        useItem = it;
        return false;
    }
    if (sec_it != nullptr && sec_it->cd_sec <= 0) {
        useItem = sec_it;
        return false;
    }
    return true;

//    float time = unit->attackCooldown;
//
//    if(time > 1 / unit->added.attackSpeed){
//        return false;
//    }
//    return true;
}
