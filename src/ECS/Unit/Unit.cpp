//
// Created by igork on 22.03.2024.
//

#include "Unit.h"

#include <utility>
#include "UnitSystem.h"
#include "ECS/Utils/Globals.h"
#include "ECS/Raycasting/CollisionSystem.h"
#include "ECS/Unit/UnitAI/UnitAI.h"
#include "ECS/Unit/UnitAI/StateMachine/States/IdleState.h"
#include "ECS/Utils/Time.h"
#include <algorithm>
#include <random>
#include "ECS/Gameplay/WashingMachine.h"
#include "ECS/Render/Components/ColorMask.h"
#include "ECS/Render/RenderSystem.h"
#include "ECS/HUD/HUD.h"
#include "ECS/Unit/UnitAI/StateMachine/States/MiningState.h"
#include "ECS/Unit/UnitAI/StateMachine/States/CombatState.h"
#include "ECS/Unit/Equipment/InventoryManager.h"
#include "ECS/Utils/CooldownComponentXDD.h"
#include "ECS/Unit/Equipment/Projectile/ProjectileSystem.h"
#include "ECS/Render/Components/ParticleEmiter.h"

const UnitStats Unit::ALLY_BASE = {
        .max_hp = 150,
        .hp = 150,
        .move_spd = 8,
        .mine_spd = 1,
        .atk_spd = 1,
        .added = {}
};

const UnitStats Unit::ENEMY_BASE_BUG = {
        .max_hp = 60,
        .hp = 60,
        .move_spd = 7,
        .mine_spd = 0,
        .atk_spd = 0.8,
        .added = {
                .def_flat = 3,
                .dmg_flat = 3,
                },
};

const UnitStats Unit::ENEMY_BASE_SHROOM = {
        .max_hp = 40,
        .hp = 40,
        .move_spd = 7,
        .mine_spd = 0,
        .atk_spd = 1.5,
        .added = {.rng_add = 3}
};


Unit::Unit(std::string name, Grid *grid, Vector2Int gridPosition, UnitStats baseStats, bool isAlly)
        : equipment(this) {
    this->name = std::move(name);
    this->grid = grid;
    this->gridPosition = gridPosition;
    this->worldPosition = grid->GridToWorldPosition(gridPosition);
    this->pathfinding = AstarPathfinding(grid, this);
    this->stats = baseStats;
    this->isAlly = isAlly;
    this->previousGridPosition = gridPosition;
    grid->getTileAt(gridPosition)->setTileState(SPONGE);
    grid->getTileAt(gridPosition)->unit = this;
    // todo switch on isAlly & randomize gabka portraits
    icon_path = "res/textures/icons/gabka_cool.png";
    mostRecentEmote = isAlly ?  ztgk::game::EMOTES::BUBBLE_CUTE : ztgk::game::EMOTES::P_BUBBLE_SAD;

    UpdateStats();
}

Unit::~Unit() {
    delete currentState;
}

bool Unit::IsAlly() const {
    return isAlly;
}

void Unit::EquipItem(Item item, short slot) {
    // todo assigning address of copied item, take by reference or pointer instead
    equipment.equipItem(&item, slot);
    UpdateStats();
}

void Unit::UnequipItem(short slot) {
    equipment.unequipItem(slot);
    UpdateStats();
}

void Unit::UpdateStats() {
    float old_max_hp = stats.max_hp + stats.added.max_hp;

    stats.added = {};
    if (equipment.item1 != nullptr) {
        stats.added += equipment.item1->stats.add_to_unit;
    }
    if (equipment.item2 != nullptr) {
        stats.added += equipment.item2->stats.add_to_unit;
    }

    equipment.rangeEff0 = equipment.item0->stats.range.merge(stats.added.rng_add, stats.added.rng_rem);
    if (equipment.item1 != nullptr)
        equipment.rangeEff1 = equipment.item1->stats.range.merge(stats.added.rng_add, stats.added.rng_rem);
    if (equipment.item2 != nullptr)
        equipment.rangeEff2 = equipment.item2->stats.range.merge(stats.added.rng_add, stats.added.rng_rem);


    stats.hp += (stats.max_hp + stats.added.max_hp) - old_max_hp;
    if (stats.hp > stats.max_hp + stats.added.max_hp) {
        stats.hp = stats.max_hp + stats.added.max_hp;
    }
}

UnitStats Unit::GetBaseStats() {
    return this->stats;
}

void Unit::showImGuiDetailsImpl(Camera *camera) {

    ImGui::Text("ID %d", uniqueID);
    ImGui::Text("Unit: %s", name.c_str());
    ImGui::Text("Current State: %s", currentState->name.c_str());
    ImGui::Text("Grid Position: (%d, %d)", gridPosition.x, gridPosition.z);
    ImGui::Text("World Position: (%f, %f, %f)", worldPosition.x, worldPosition.y, worldPosition.z);
    ImGui::Text("Ally: %s", isAlly ? "true" : "false");
    ImGui::Text("Selected: %s", isSelected ? "true" : "false");
    ImGui::Text("HP %f / %f (%f + %f)", stats.hp, stats.max_hp + stats.added.max_hp, stats.max_hp, stats.added.max_hp);
    if (ImGui::CollapsingHeader(std::format("Added stats:##+stats_unit_{}", uniqueID).c_str())) {
        stats.added.imgui_preview();
    }
    if (ImGui::CollapsingHeader(std::format("Equipment:##eq_unit_{}", uniqueID).c_str()))
        equipment.imgui_preview();
    ImGui::Text("Has movement target? %s", hasMovementTarget ? "true" : "false");
    ImGui::Text("Movement Target: (%d, %d)", movementTarget.x, movementTarget.z);
    ImGui::Text("Has combat target? %s", hasCombatTarget ? "true" : "false");
    ImGui::Text("Combat Target: %s (%d, %d)",
                combatTarget != nullptr ? combatTarget->name.c_str() : "This sponge is pacifist",
                combatTarget != nullptr ? combatTarget->gridPosition.x : 0,
                combatTarget != nullptr ? combatTarget->gridPosition.z : 0);
    ImGui::Text("Has mining target? %s", hasMiningTarget ? "true" : "false");
    ImGui::Text("Mining Target: %s (%d, %d)",
                currentMiningTarget != nullptr ? currentMiningTarget->name.c_str() : "No mining target",
                currentMiningTarget != nullptr ? currentMiningTarget->gridPosition.x : 0,
                currentMiningTarget != nullptr ? currentMiningTarget->gridPosition.z : 0);
    ImGui::Text("Has pickup target? %s", hasPickupTarget ? "true" : "false");
    ImGui::Text("Pickup Target: %s (%f, %f, %f)",
                pickupTarget != nullptr ? pickupTarget->name.c_str() : "No pickup target",
                pickupTarget != nullptr ? pickupTarget->getEntity()->transform.getGlobalPosition().x : 0,
                pickupTarget != nullptr ? pickupTarget->getEntity()->transform.getGlobalPosition().y : 0,
                pickupTarget != nullptr ? pickupTarget->getEntity()->transform.getGlobalPosition().z : 0);
    ImGui::Separator();
    ImGui::Text("Forced movement state? %s", ForcedMovementState ? "true" : "false");
    ImGui::Text("Forced movement target: (%d, %d)", forcedMovementTarget.x, forcedMovementTarget.z);
}

void Unit::UpdateImpl() {
    if(firstUpdate){
        onFirstUpdate();
    }
    animationcooldown += Time::Instance().DeltaTime();


    if (stats.hp <= 0) {
        isAlive = false;
    }

    if (isBeingHealedByWashingMachine && stats.hp >= stats.max_hp) {
        isBeingHealedByWashingMachine = false;
    }

    if (isAlly) {
        float dirtLvl = 1 - (stats.hp / (stats.max_hp + stats.added.max_hp));
        auto render = getEntity()->getComponent<Render>();
        if (render != nullptr) {
            render->dirtLevel = dirtLvl;
        }
    }
    if (!isAlive && isAlly) {
        gridPosition = grid->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(worldPosition));

        ztgk::game::scene->systemManager.getSystem<UnitSystem>()->deselectUnit(this);
        //if unit stands next to washing machine it will be healed by it
        auto neighTiles = grid->GetNeighbours(gridPosition, true);
        for (auto &tile: neighTiles) {
            if (tile != nullptr && tile->getEntity()->getComponent<WashingMachineTile>() != nullptr) {
                isBeingHealedByWashingMachine = true;
            }
        }

        //if unit has 0 hp but is not next to washing machine it will path to washing machine with 50% speed
        if (!isBeingHealedByWashingMachine) {
            movementTarget = pathfinding.GetNearestVacantTile(getClosestWashingMachineTile(), gridPosition);
            hasMovementTarget = true;
        }
    }
    if (!isAlive && !isAlly) {
        isDestinedToDie = true;

        return;
    }

    if (isAlive) {
        gridPosition = grid->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(worldPosition));
        auto currentTile = grid->getTileAt(gridPosition);
        if(isAlly){
            auto n = grid->GetNeighbours(gridPosition, true);
            n.push_back(currentTile);
            for(auto &neigh : n){
                if(neigh->vacant()) {
                    auto newDirtLvl = neigh->dirtinessLevel - 90 * Time::Instance().DeltaTime();
                    if (newDirtLvl < 0) {
                        newDirtLvl = 0;
                    }
                    neigh->changeDirtinessLevel(newDirtLvl);
                    if(newDirtLvl == 0 && neigh->particle_sent == false){
                        neigh->tryToSendParticle(RNG::RandomBool()? 3 : 4);
                        neigh->particle_sent = true;
                    }
                }
            }
        }else{
            auto n = grid->GetNeighbours(gridPosition, true);
            n.push_back(currentTile);
            for(auto &neigh : n){
                if(neigh->vacant()) {
                    auto newDirtLvl = neigh->dirtinessLevel + 30 * Time::Instance().DeltaTime();
                    if (newDirtLvl > 100) {
                        newDirtLvl = 100;
                    }
                    neigh->changeDirtinessLevel(newDirtLvl);
                }
            }
        }


        if (combatTarget != nullptr &&  !combatTarget->isAlive ) {
            combatTarget = nullptr;
            hasCombatTarget = false;
        }


        if (currentMiningTarget != nullptr && currentMiningTarget->isMined) {
            currentMiningTarget = nullptr;
        }

        for (auto &mineable: miningTargets) {
            if (mineable->isMined) {
                miningTargets.erase(std::remove(miningTargets.begin(), miningTargets.end(), mineable),
                                    miningTargets.end());
            }
        }
        if(hasMiningTarget) {
            if (currentMiningTarget == nullptr) {
                //erease currentMiningTarget from miningTargets
                miningTargets.erase(std::remove(miningTargets.begin(), miningTargets.end(), currentMiningTarget),
                                    miningTargets.end());
                currentMiningTarget = findClosestMineable();
                if (currentMiningTarget == nullptr) {
                    hasMiningTarget = false;
                } else {
                    hasMiningTarget = true;
                }

            }
            if(currentMiningTarget != nullptr && checkIfMaybeOtherUnitHasThisIMineableComponentAsThierCurrentMiningTargetAndReturnBooleanSayingTrueIfItHasAndFalseIfItDoesNot()){
                miningTargets.erase(std::remove(miningTargets.begin(), miningTargets.end(), currentMiningTarget),
                                    miningTargets.end());
                currentMiningTarget = findClosestMineable();
            }
        }

        if (hasMovementTarget) {
            if (!grid->getTileAt(movementTarget)->vacant()) {
                movementTarget = pathfinding.GetNearestVacantTile(movementTarget, gridPosition);
                pathfinding.path = pathfinding.FindPath(gridPosition, movementTarget);
            }
        }

        if (ForcedMovementState) {
            if (!hasMovementTarget) {
                ForcedMovementState = false;
            } else {
                hasMiningTarget = false;
                hasCombatTarget = false;
                hasMovementTarget = true;
                combatTarget = nullptr;
                miningTargets.clear();
                currentMiningTarget = nullptr;
                movementTarget = forcedMovementTarget;
                if (!grid->getTileAt(forcedMovementTarget)->vacant()) {
                    movementTarget = pathfinding.GetNearestVacantTile(forcedMovementTarget, gridPosition);
                    forcedMovementTarget = movementTarget;
                }
            }
        }


        static GridRange searchRange{4, 0};

        if (!hasCombatTarget) {
            if (isAlly) {
                GridRange *maxRange;
                if (equipment.use_default()) {
                    maxRange = &equipment.rangeEff0;
                } else if (equipment.item1 && equipment.item1->offensive && equipment.item2 &&
                           equipment.item2->offensive) {
                    maxRange = equipment.rangeEff1.add >= equipment.rangeEff2.add ? &equipment.rangeEff1
                                                                                  : &equipment.rangeEff2;
                } else if (equipment.item1 && equipment.item1->offensive) {
                    maxRange = &equipment.rangeEff1;
                } else if (equipment.item2 && equipment.item2->offensive) {
                    maxRange = &equipment.rangeEff2;
                }
                searchRange = GridRange(maxRange->add + 1, maxRange->remove);
            }

            auto in_search_range = searchRange.find_my_enemies(VectorUtils::Vector2IntToGlmVec2(gridPosition), isAlly);
            if (!in_search_range.empty()) {
                std::sort(in_search_range.begin(), in_search_range.end(), [this](Unit *a, Unit *b) {
                    return VectorUtils::GridDistance(this->gridPosition, a->gridPosition) <
                           VectorUtils::GridDistance(this->gridPosition, b->gridPosition);
                });
                combatTarget = in_search_range.at(0);
            }
        }

        if (combatTarget != nullptr && !ForcedMovementState) {
            hasCombatTarget = true;
            auto combatState = new CombatState(grid);
            combatState->unit = this;
            if (combatState->isTargetInRange() && canPathToAttackTarget()) { delete combatState; }
            else if (!combatState->isTargetInRange() && canPathToAttackTarget()) {
                hasMovementTarget = true;

                movementTarget = pathfinding.GetNearestVacantTileInRange(combatTarget->gridPosition, gridPosition,
                                                                         stats.added.rng_add + stats.added.rng_rem);
                delete combatState;
            } else {
                hasCombatTarget = false;
                delete combatState;
            }
        } else {
            hasCombatTarget = false;
        }
    }

    if (combatTarget != nullptr && !combatTarget->isAlive) {
        combatTarget = nullptr;
        hasCombatTarget = false;
    }

    if (gridPosition != previousGridPosition) {
        grid->getTileAt(previousGridPosition)->setTileState(FLOOR);
        grid->getTileAt(gridPosition)->setTileState(SPONGE);
        grid->getTileAt(previousGridPosition)->unit = nullptr;
        grid->getTileAt(gridPosition)->unit = this;
        auto emote =ztgk::game::EMOTES::BUBBLE_TONGUE;
        auto randInt = RNG::RandomInt(0, 2);
        if(isAlly){
            switch (randInt) {
                case 0:
                    emote = ztgk::game::EMOTES::BUBBLE_TONGUE;
                    break;
                case 1:
                    emote = ztgk::game::EMOTES::BUBBLE_HAPPY;
                    break;
                case 2:
                    emote = ztgk::game::EMOTES::BUBBLE_CUTE;
                    break;
            }
        } else{
            switch (randInt) {
                case 0:
                    emote = ztgk::game::EMOTES::P_BUBBLE_TONGUE;
                    break;
                case 1:
                    emote = ztgk::game::EMOTES::P_BUBBLE_CUTE;
                    break;
                case 2:
                    emote = ztgk::game::EMOTES::P_BUBBLE_EEPY;
                    break;
            }

        }

        tryToSendEmote(emote);

        speaker->PlayRandomSoundFromGroup(isAlly ? "gabka" : "bug");
        auto anim = getEntity()->getComponent<AnimationPlayer>();
        if (anim == nullptr) {
            spdlog::error("No animation player component found");
        } else if(unitType == UNIT_SPONGE){
            string modelPathGabkaMove = "res/models/gabka/pan_gabka_move.fbx";
            anim->PlayAnimation(modelPathGabkaMove, false, 6.0f);
        }
    }

    getEntity()->transform.setLocalPosition(worldPosition);
    const float rotationSpeed = 0.1f; // The speed at which to rotate each frame
    float deltaRotation = rotation - currentRotation;

// Normalize the deltaRotation to be within the range [-180, 180]
    if (deltaRotation > 180.0f) {
        deltaRotation -= 360.0f;
    }
    if (deltaRotation < -180.0f) {
        deltaRotation += 360.0f;
    }

// Apply the rotation
    if (deltaRotation > 0.1f) {
        currentRotation += rotationSpeed;
    } else if (deltaRotation < -0.1f) {
        currentRotation -= rotationSpeed;
    } else {
        currentRotation = rotation; // Snap to the target rotation when close enough
    }

    getEntity()->transform.setLocalRotation(glm::vec3(0, currentRotation, 0));

    if ((equipment.item1 != nullptr && equipment.item1->name == "Pranium Ore") ||
        (equipment.item2 != nullptr && equipment.item2->name == "Pranium Ore")) {
        std::vector<Tile *> neighTiles = grid->GetNeighbours(gridPosition);
        for (auto &tile: neighTiles) {
            if (tile->getTileState() == TileState::CORE) {
                if (equipment.item1 != nullptr && equipment.item1->name == "Pranium Ore") {
                    equipment.unequipItem(1);
                    ztgk::game::scene->systemManager.getSystem<WashingMachine>()->onPraniumDelivered();
                } else if (equipment.item2 != nullptr && equipment.item2->name == "Pranium Ore") {
                    equipment.unequipItem(2);
                    ztgk::game::scene->systemManager.getSystem<WashingMachine>()->onPraniumDelivered();
                }
            }
        }
    }

    auto cm = getEntity()->getComponent<ColorMask>();
    if (isSelected) {
        if (cm == nullptr) {
            getEntity()->addComponent(make_unique<ColorMask>());
            cm = getEntity()->getComponent<ColorMask>();
        }
        if (!cm->HasMask("selected")) {
            cm->AddMask("selected", glm::vec4(0, 150.0f / 250.0f, 20.0f / 250.0f, 0.3f));
        }
    } else if (!isSelected && cm != nullptr && cm->HasMask("selected")) {
        cm->RemoveMask("selected");
    }

    getEntity()->getComponent<Render>()->isInFogOfWar = grid->getTileAt(gridPosition)->isInFogOfWar;


    previousGridPosition = gridPosition;

    if (equipment.item0->cd_sec > 0)
        equipment.item0->cd_sec -= Time::Instance().DeltaTime() * (stats.atk_spd + stats.added.atk_speed);
    if (equipment.item1 != nullptr && equipment.item1->cd_sec > 0)
        equipment.item1->cd_sec -= Time::Instance().DeltaTime() * (stats.atk_spd + stats.added.atk_speed);
    if (equipment.item2 != nullptr && equipment.item2->cd_sec > 0)
        equipment.item2->cd_sec -= Time::Instance().DeltaTime() * (stats.atk_spd + stats.added.atk_speed);
    if (equipment.cd_between_sec > 0)
        equipment.cd_between_sec -= Time::Instance().DeltaTime() * (stats.atk_spd + stats.added.atk_speed);

    if (isAlive) {
        // item has an ability with cooldown but isn't used for attack
        if (equipment.item1 && equipment.item1->active && equipment.item1->cd_sec <= 0) {
            auto target = equipment.item1->determine_target(this);
            if (target) {
                CombatState::AttackSideFX(equipment.item1, this, target);
            }
        }
        if (equipment.item2 && equipment.item2->active && equipment.item2->cd_sec <= 0) {
            auto target = equipment.item2->determine_target(this);
            if (target) {
                CombatState::AttackSideFX(equipment.item2, this, target);
            }
        }
    }

    if (isAlly) {
        Entity *child = parentEntity->getChild("RHand");
        AnimationPlayer *player;
        if (child) {
            player = getEntity()->getComponent<AnimationPlayer>();
            if (player)    {
                player->animator.UpdateNodes();
                std::vector<glm::mat4> finalBoneMatrices =   player->animator.GetFinalNodeMatrices();
                child->transform.setLocalMatrix(finalBoneMatrices[player->animator.m_CurrentAnimation->GetBoneIdFromName("Hand.R")])  ;
            }

        }
        child = parentEntity->getChild("LHand");
        if (child) {
            player = getEntity()->getComponent<AnimationPlayer>();
            if (player){
                player->animator.UpdateNodes();
                std::vector<glm::mat4> finalBoneMatrices =   player->animator.GetFinalNodeMatrices();
                child->transform.setLocalMatrix(finalBoneMatrices[player->animator.m_CurrentAnimation->GetBoneIdFromName("Hand.L")]);
            }
        }
    }

}

Unit *Unit::GetClosestEnemyInWeaponRange() {
    std::vector<Unit *> enemies;

    if (equipment.use_default()) {
        return equipment.item0->determine_target(this);
    }

    if (equipment.item1 != nullptr && equipment.item1->offensive) {
        auto target = equipment.item1->determine_target(this);
        if (target)
            enemies.push_back(target);
    }
    if (equipment.item2 != nullptr && equipment.item2->offensive) {
        auto target = equipment.item2->determine_target(this);
        if (target)
            enemies.push_back(target);
    }

    if (enemies.empty())
        return nullptr;

    // this just compares 2 values at most now
    std::sort(enemies.begin(), enemies.end(), [this](Unit *enemy, Unit *enemy1) {
        return VectorUtils::GridDistance(this->gridPosition, enemy->gridPosition) <
               VectorUtils::GridDistance(this->gridPosition, enemy1->gridPosition);
    });
    return enemies.at(0);
//

}

bool Unit::canFindPathToTarget(Vector2Int target) {
    pathfinding.FindPath(gridPosition, target,
                         ztgk::game::scene->systemManager.getSystem<UnitSystem>()->getAllUnitsPositionsExceptMe(this));
    return !pathfinding.path.empty();
}

void Unit::serializer_init(Grid *pGrid) {
    auto playerUnit = getEntity();
    auto stateManager = new StateManager(playerUnit->getComponent<Unit>());
    stateManager->currentState = new IdleState(pGrid);
    stateManager->currentState->unit = playerUnit->getComponent<Unit>();
    playerUnit->addComponent(make_unique<UnitAI>(playerUnit->getComponent<Unit>(), stateManager));

    // the rest is taken care of by the serializer, all we set here are extra assignments that aren't just a param copy (except for the pGrid ptr)
    this->grid = pGrid;
    this->worldPosition = pGrid->GridToWorldPosition(gridPosition);
    this->pathfinding = AstarPathfinding(pGrid, this);
    this->previousGridPosition = gridPosition;
    UpdateStats();
}

Entity *Unit::serializer_newUnitEntity(Scene *scene, const std::string &name) {
    auto playerUnit = scene->addEntity(name);
    playerUnit->addComponent(make_unique<Render>(ztgk::game::cube_model));
    playerUnit->transform.setLocalScale(glm::vec3(1, 1, 1));
    playerUnit->transform.setLocalRotation(glm::vec3(0, 0, 0));
    playerUnit->updateSelfAndChild();
    playerUnit->addComponent(make_unique<BoxCollider>(playerUnit, glm::vec3(2, 2, 2)));
    playerUnit->getComponent<BoxCollider>()->setCenter(
            playerUnit->transform.getGlobalPosition() + glm::vec3(0, 0, 0.5));
    playerUnit->addComponent(make_unique<Unit>());
    return playerUnit;
}

IMineable *Unit::findClosestMineable(const std::vector<IMineable> &MineablesToExclude) {
    ZoneScopedN("Find closest mineable");

    if (miningTargets.empty()) {
        spdlog::error("IN SPONGE::findClosestMineable: No mining targets!");
        return nullptr;
    }

    IMineable *closestMineable = nullptr;
    float closestDistance = std::numeric_limits<float>::max();  // Use the maximum float value

    for (auto tile : miningTargets) {
        bool isExcluded = false;
        for (auto &excluded : MineablesToExclude) {
            if (tile->gridPosition == excluded.gridPosition) {
                isExcluded = true;
                break;  // Stop checking other exclusions
            }
        }

        if (isExcluded) {
            continue;  // Skip excluded targets
        }

        float distance = VectorUtils::Distance(Vector2Int(gridPosition.x, gridPosition.z),
                                               Vector2Int(tile->gridPosition.x, tile->gridPosition.z));

        if (distance < closestDistance) {
            auto neighbors = grid->GetNeighbours(tile->gridPosition);
            bool isNeighbor = false;
            for (auto &neighbor : neighbors) {
                if (neighbor->index == gridPosition) {
                    isNeighbor = true;
                    break;  // Target is a direct neighbor
                }
            }

            if (isNeighbor || !pathfinding.FindPath(gridPosition, pathfinding.GetNearestVacantTile(tile->gridPosition, gridPosition)).empty()) {
                closestDistance = distance;
                closestMineable = tile;
            }
        }
    }

    if (closestMineable == nullptr) {
        spdlog::error("IN SPONGE::findClosestMineable: No reachable mining target in area!");
    }

    return closestMineable;
}

std::vector<Unit *> Unit::GetPathableEnemiesInSight() {
    std::vector<Unit *> enemies;
    int sightRange = isAlly ? 6 : 4;
    for (int i = -sightRange; i < sightRange; i++) {
        for (int j = -sightRange; j < sightRange; j++) {
            Vector2Int pos = Vector2Int(gridPosition.x + i, gridPosition.z + j);
            if (grid->isInBounds(pos)) {
                Tile *tile = grid->getTileAt(pos);
                if (tile->unit != nullptr && tile->unit->IsAlly() != isAlly) {
                    enemies.push_back(tile->unit);

                }
            }
        }
    }

    for (auto enemy: enemies) {
        if (!canPathToAttackTarget(enemy)) {
            enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
        }
    }

    //remove enemies that are not alive
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Unit *enemy) {
        return !enemy->isAlive;
    }), enemies.end());

    return enemies;
}

Unit *Unit::GetClosestPathableEnemyInSight() {
    std::vector<Unit *> enemies = GetPathableEnemiesInSight();
    if (enemies.empty())
        return nullptr;

    std::sort(enemies.begin(), enemies.end(), [this](Unit *enemy, Unit *enemy1) {
        return VectorUtils::Distance(this->gridPosition, enemy->gridPosition) <
               VectorUtils::Distance(this->gridPosition, enemy1->gridPosition);
    });
    //remove enemies that are not alive
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Unit *enemy) {
        return !enemy->isAlive;
    }), enemies.end());

    return enemies.at(0);
}

Vector2Int Unit::GetDirtiestTileAround() {
    int dirtiestLevel = 0;
    Vector2Int dirtiestTile = gridPosition;
    std::vector<Vector2Int> positions;

    // Populate positions within a 2-tile radius
    for (int x = -2; x <= 2; ++x) {
        for (int y = -2; y <= 2; ++y) {
            if (x != 0 || y != 0) {  // Exclude the current position
                positions.push_back(Vector2Int(x, y));
            }
        }
    }

    // Randomize the positions vector
    std::shuffle(positions.begin(), positions.end(), std::mt19937(std::random_device()()));

    for (auto &offset: positions) {
        Vector2Int pos = gridPosition + offset;
        if (grid->isInBounds(pos)) {
            Tile *tile = grid->getTileAt(pos);
            if (tile->dirtinessLevel > dirtiestLevel) {
                dirtiestLevel = tile->dirtinessLevel;
                dirtiestTile = pos;
            }
        }
    }
    return dirtiestTile;
}


void Unit::DIEXD() {
    if (ztgk::game::ui_data.tracked_unit_id == uniqueID) {
        ztgk::game::scene->systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_middle)->setHidden(
                true);
        ztgk::game::ui_data.tracked_unit_id = -1;
    }

    grid->getTileAt(gridPosition)->unit = nullptr;
    grid->getTileAt(gridPosition)->setTileState(FLOOR);
    ztgk::game::scene->systemManager.getSystem<UnitSystem>()->removeComponent(this);
    ztgk::game::scene->systemManager.getSystem<RenderSystem>()->removeComponent(getEntity()->getComponent<Render>());
    ztgk::game::scene->systemManager.getSystem<RenderSystem>()->removeColorMaskComponent(
            getEntity()->getComponent<ColorMask>());

    //look for every unit that has opposite isAlly and remove this unit from their combatTargets
    for (auto &unit: ztgk::game::scene->systemManager.getSystem<UnitSystem>()->unitComponents) {
        if (unit->IsAlly() != isAlly) {
            if (unit->combatTarget == this) {
                unit->combatTarget = nullptr;
                unit->hasCombatTarget = false;
            }
        }
    }

    //remove all projectiles that target or come from this unit (the projectile will handle this on its update)
    for (auto projectile : ztgk::game::scene->systemManager.getSystem<ProjectileSystem>()->projectiles
        | std::views::filter([this](Projectile *projectile) { return projectile->unit == this || projectile->target == this; })) {
        projectile->unit = nullptr;
        projectile->target = nullptr;
    }

    InventoryManager::instance->unassign_item(this, short(0));
    if(equipment.item1)
        InventoryManager::instance->unassign_item(this, 1);
    if(equipment.item2)
        InventoryManager::instance->unassign_item(this, 2);

    getEntity()->Destroy();

}

bool Unit::canPathToAttackTarget(Unit *target) {
    if (target == nullptr) {
        target = combatTarget;
    }
    if (target == nullptr) {
        return false;
    }
    auto neigh = grid->GetNeighbours(target->gridPosition);
    for (auto n: neigh) {
        if (n->index == gridPosition) {
            return true;
        }
    }
    auto nearestVacant = pathfinding.GetNearestVacantTile(target->gridPosition, gridPosition);
    if (nearestVacant == gridPosition) {
        return false;
    }
    auto pathToTarget = pathfinding.FindPath(gridPosition, nearestVacant);
    return !pathToTarget.empty();
}

bool Unit::canPathToMiningTarget() {
    if (currentMiningTarget == nullptr) {
        return false;
    }
    auto neigh = grid->GetNeighbours(currentMiningTarget->gridPosition);
    for (auto n: neigh) {
        if (n->index == gridPosition) {
            return true;
        }
    }
    auto pathToTarget = pathfinding.FindPath(gridPosition,
                                             pathfinding.GetNearestVacantTile(currentMiningTarget->gridPosition, gridPosition)
                                                                              );
    return !pathToTarget.empty();
}

Unit *Unit::GetClosestEnemyInSight() {
    std::vector<Unit *> enemies;
    int sightRange = isAlly ? 6 : 4;
    for (int i = -sightRange; i < sightRange; i++) {
        for (int j = -sightRange; j < sightRange; j++) {
            Vector2Int pos = Vector2Int(gridPosition.x + i, gridPosition.z + j);
            if (grid->isInBounds(pos)) {
                Tile *tile = grid->getTileAt(pos);
                if (tile->unit != nullptr && tile->unit->IsAlly() != isAlly) {
                    enemies.push_back(tile->unit);
                }
            }
        }
    }

    if (enemies.empty())
        return nullptr;

    std::sort(enemies.begin(), enemies.end(), [this](Unit *enemy, Unit *enemy1) {
        return VectorUtils::Distance(this->gridPosition, enemy->gridPosition) <
               VectorUtils::Distance(this->gridPosition, enemy1->gridPosition);
    });
    return enemies.at(0);
}

void Unit::Pickup(PickupubleItem *item) {
    std::pair<Item *, Item *> drop = InventoryManager::instance->assign_item(pickupTarget->item, this, -1);

    auto target = pickupTarget;
    auto spawn_origin = target->gridPosition;
    for (auto unit: ztgk::game::scene->systemManager.getSystem<UnitSystem>()->allies) {
        if (unit->hasPickupTarget && unit->pickupTarget == target) {
            unit->hasPickupTarget = false;
            unit->pickupTarget = nullptr;
        }
    }
    grid->getTileAt(target->gridPosition)->setTileState(FLOOR);
    target->getEntity()->getComponent<Render>()->Remove();
    target->Remove();

    Vector2Int first_pos = pathfinding.GetNearestVacantTileAround(spawn_origin, {spawn_origin});
    if (drop.first)
        InventoryManager::instance->spawn_item_on_map(drop.first, first_pos);
    if (drop.second)
        InventoryManager::instance->spawn_item_on_map(
                drop.second,
                pathfinding.GetNearestVacantTileAround(spawn_origin,drop.first ? std::vector{spawn_origin,first_pos} : std::vector{spawn_origin}));
}

Vector2Int Unit::getClosestWashingMachineTile() {
    std::vector<Vector2Int> washingMachineTilesGridPos;
    auto washingMachineTileMap = ztgk::game::scene->systemManager.getSystem<WashingMachine>()->WashingMachineTiles;
    for (auto &tile: washingMachineTileMap) {
        washingMachineTilesGridPos.push_back(tile.second[0]->gridPosition);
    }

    //sort by distance to unit
    std::sort(washingMachineTilesGridPos.begin(), washingMachineTilesGridPos.end(),
              [this](Vector2Int pos1, Vector2Int pos2) {
                  return VectorUtils::Distance(this->gridPosition, pos1) <
                         VectorUtils::Distance(this->gridPosition, pos2);
              });

    return washingMachineTilesGridPos[0];
}

void Unit::tryToSendEmote(ztgk::game::EMOTES emote, float time) {
    if (getEntity()->getChild("Emote") == nullptr) {
        ztgk::game::scene->addEntity(getEntity(), "Emote");
    }
    auto emoChild = getEntity()->getChild("Emote");

    if(emoChild->getComponent<CooldownComponentXDD>() != nullptr){
        emoChild->getComponent<CooldownComponentXDD>()->UpdateImpl();
        return;
    }

    if (emoChild->getComponent<BetterSpriteRender>() == nullptr) {
        emoChild->addComponent(std::make_unique<BetterSpriteRender>(ztgk::game::emotes.at(emote).get() , 2));
        mostRecentEmote = emote;
    }
    else if(emoChild->getComponent<BetterSpriteRender>() != nullptr && emoChild->getComponent<BetterSpriteRender>()->toBeDeleted) {
        emoChild->removeComponentFromMap(emoChild->getComponent<BetterSpriteRender>());
    }

}

void Unit::onFirstUpdate() {
    getEntity()->addComponent(std::make_unique<Speaker>());
    speaker = parentEntity->getComponent<Speaker>();

    firstUpdate = false;
}

bool Unit::checkIfMaybeOtherUnitHasThisIMineableComponentAsThierCurrentMiningTargetAndReturnBooleanSayingTrueIfItHasAndFalseIfItDoesNot(){
    for (auto &unit: ztgk::game::scene->systemManager.getSystem<UnitSystem>()->unitComponents) {
        if(unit == this){
            continue;
        }
        if (unit->isAlly && unit->hasMiningTarget && unit->currentMiningTarget == currentMiningTarget) {
            return true;
        }
    }
    return false;
}



