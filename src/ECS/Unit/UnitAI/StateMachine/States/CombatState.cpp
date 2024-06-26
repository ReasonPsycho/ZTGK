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
#include "ECS/Render/Components/AnimationPlayer.h"
#include "ECS/Render/Components/BetterSpriteRender.h"

State *CombatState::RunCurrentState() {
    unit->playinIdleAnimation = false;
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
                unit->movementTarget = unit->pathfinding.GetNearestVacantTile(closestMineable->gridPosition, unit->gridPosition);
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
    if(!isTargetInRange()){
        unit->hasMovementTarget = true;
        unit->movementTarget = unit->combatTarget->gridPosition;
        return;
    }
    float angle = atan2(unit->combatTarget->worldPosition.x - unit->worldPosition.x, unit->combatTarget->worldPosition.z - unit->worldPosition.z);
    unit->rotation = angle;

    auto target = unit->combatTarget;
    if(target == nullptr) return; //todo expand on this

    AttackSideFX(useItem, unit, target);
}

void CombatState::AttackSideFX(Item * useItem, Unit * unit, Unit * target) {
    useItem->cd_sec = useItem->stats.cd_max_sec;
    unit->equipment.cd_between_sec = unit->equipment.cd_between_max_sec;

    useItem->do_attack(unit, target);

    auto anim = unit->getEntity()->getComponent<AnimationPlayer>();
    if(anim == nullptr) {
        spdlog::error("No animation player component found");
    } else if(unit->unitType == UnitType::UNIT_SPONGE) {
        //if unit has default weapon or has 2 weapons, change attack animation based on last used attack - right or left
        if(unit->equipment.use_default() || (unit->equipment.item1 != nullptr && unit->equipment.item2 != nullptr)){
            if(unit->lastUsedRightAttack){
                string modelPathGabkaMove = "res/models/gabka/pan_gabka_attack_left.fbx";
                anim->PlayAnimation(modelPathGabkaMove, false, 5.0f);

            }
            else{
                string modelPathGabkaMove = "res/models/gabka/pan_gabka_attack_right.fbx";
                anim->PlayAnimation(modelPathGabkaMove, false, 5.0f);
            }
            unit->lastUsedRightAttack = !unit->lastUsedRightAttack;
        }
        else{
            if(unit->equipment.item1 != nullptr){
                string modelPathGabkaMove = "res/models/gabka/pan_gabka_attack_left.fbx";
                anim->PlayAnimation(modelPathGabkaMove, false, 5.0f);
            }
            else if(unit->equipment.item2 != nullptr){
                string modelPathGabkaMove = "res/models/gabka/pan_gabka_attack_right.fbx";
                anim->PlayAnimation(modelPathGabkaMove, false, 5.0f);
            }
        }
    } else if(unit->unitType == UNIT_BUG){
        string modelPathBugMove = "res/models/zuczek/Zuczek_attack - copia.fbx";
        anim->PlayAnimation(modelPathBugMove, false, 5.0f);
    } else if(unit->unitType == UNIT_SHROOM){
        string modelPathShroomMove = "res/models/Mushroom/shroom_spit.fbx";
        anim->PlayAnimation(modelPathShroomMove, false, 5.0f);
    }
    // todo highlight tiles, play particles
}

void CombatState::applyDamage(Unit *unit, Unit* target, float damage) {
    target->stats.hp -= damage;
    // avoid overheal
    if (target->stats.hp > target->stats.max_hp + target->stats.added.max_hp)
        target->stats.hp = target->stats.max_hp + target->stats.added.max_hp;

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

    if (damage < 0) { // heal
        // do_heal flashes tiles green-ish here
        // todo make tile flash this color too
        cm->AddMask("Healing", glm::vec4(0, 255, 0, 255), 0.25f);
        ztgk::game::audioManager->playRandomSoundFromGroup("heal");
        target->tryToSendEmote(unit->isAlly ? ztgk::game::EMOTES::BUBBLE_TONGUE : ztgk::game::EMOTES::P_BUBBLE_TONGUE);
    } else {
        ztgk::game::scene->systemManager.getSystem<Grid>()->getTileAt(target->gridPosition)->setHighlightOverride(DAMAGE_LIGHT_RED, 0.25f);
        cm->AddMask("DMG_taken", {200.0f/250.0f, 0, 0, 0.5f}, 0.25f);
        ztgk::game::audioManager->playRandomSoundFromGroup("punch");
        target->tryToSendEmote(target->isAlly ? (RNG::RandomBool() ? ztgk::game::EMOTES::Y_BUBBLE_ANGRY : ztgk::game::EMOTES::Y_BUBBLE_SAD) : ztgk::game::EMOTES::P_BUBBLE_SAD);
    }

    if(target->stats.hp <= 0){
        unit->speaker->PlayRandomSoundFromGroup(target->isAlly ? "deathSponge" : "deathEnemy");

        unit->hasCombatTarget = false;
        target->isAlive = false;
        unit->combatTarget = nullptr;

        if(!target->isAlly){
            target->isAlive = false;
            target->flingDirection = target->calculateFlingDirection(unit->gridPosition);
        }
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

}
