#include "CombatState.h"
#include "ECS/Unit/Unit.h"
#include "ECS/Unit/UnitAI/StateMachine/State.h"
#include "MovementState.h"
#include "MiningState.h"
#include "IdleState.h"

// Static member initialization
std::unique_ptr<CombatState> CombatState::instance = nullptr;

// Constructor
CombatState::CombatState(Grid* grid, Unit* unit){
    this->name = "Combat";
    this->grid = grid;
    this->unit = unit;
}

// Static method to get the instance of CombatState
std::unique_ptr<CombatState> CombatState::getInstance(Grid* grid, Unit* unit) {
    if (!instance) {
        instance = std::unique_ptr<CombatState>(new CombatState(grid, unit));
    }
    return std::unique_ptr<CombatState>(instance.get());
}

// Method to run the current state
std::unique_ptr<State> CombatState::RunCurrentState() {

    //from Combat to Idle
    if (!unit->hasMovementTarget && !unit->hasCombatTarget && !unit->hasMiningTarget) {
        auto idleState = IdleState::getInstance(grid, unit);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(1.5, 5.0);
        double random_number = dis(gen);

        idleState->randomTime = random_number;

        return std::move(idleState);
    }

    //from Combat to Movement
    if (unit->hasMovementTarget) {
        auto moveState = MovementState::getInstance(grid, unit);

        return std::move(moveState);
    }

    //from Combat to Mining
    if (unit->hasMiningTarget) {
        auto miningState = MiningState::getInstance(grid, unit);

        if(miningState->isTargetInRange())
            return std::move(miningState);
        else
        {
            auto moveState = MovementState::getInstance(grid, unit);
            unit->hasMovementTarget = true;
            unit->movementTarget = unit->findClosestMineable()->gridPosition;
            return std::move(moveState);
        }
    }

    AttackTarget();
    return getInstance(grid, unit);
}

bool CombatState::isTargetInRange() {
    if(unit->combatTarget == nullptr){
        unit->hasCombatTarget = false;
        return false;
    }

    Unit* targ = unit->GetClosestEnemyInWeaponRange();
    if (targ == nullptr) {
        unit->hasCombatTarget = false;
        unit->isTargetInRange = false;
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
    float angle = atan2(unit->combatTarget->gridPosition.z - unit->gridPosition.z, unit->combatTarget->gridPosition.x - unit->gridPosition.x);
    unit->rotation = angle;

    auto target = unit->combatTarget;

    float totalAttackDamage =
            (useItem->stats.dmg * unit->stats.added.dmg_perc + unit->stats.added.dmg_flat)
            * (1 - target->stats.added.def_perc) - target->stats.added.def_flat;

    useItem->cd_sec = useItem->stats.cd_max_sec;
    unit->equipment.cd_between_sec = unit->equipment.cd_between_max_sec;
    target->stats.hp -= totalAttackDamage;
    spdlog::info("Unit {} attacked unit {} for {} damage", unit->name, target->name, totalAttackDamage);

    if(target->stats.hp <= 0){
        unit->hasCombatTarget = false;
        target->parentEntity->Destroy();
        unit->combatTarget = nullptr;
    }
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

    Item * it;
    Item * sec_it;
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

    if (it != nullptr && it->cd_sec < 0) {
        useItem = it;
        return false;
    }
    if (sec_it != nullptr && sec_it->cd_sec < 0) {
        useItem = sec_it;
        return false;
    }
    return true;
}