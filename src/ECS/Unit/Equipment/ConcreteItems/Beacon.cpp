//
// Created by cheily on 24.06.2024.
//
#include "ECS/Unit/Equipment/ConcreteItems/Beacon.h"
#include "ECS/Unit/Unit.h"

Beacon::Beacon() : Item("Soap Refill", "Refresh for the bravest!", false, ItemStats(5, 10, GridRange(4, 0), GridRange(0, 0)), true) {
    active = true;
    icon_path = "res/textures/icons/item_beacon.png";
    model = ztgk::game::tidyPodLauncherModel; // todo change model

    determine_target = [this](Unit * me) { return Item::determine_healing_target(me, me->equipment.range_of(this)); };
    do_attack = [this](Unit * me, Unit * target){ Item::do_heal(me, target, this); };
    determine_damage = [this](Unit * me, Unit * target, glm::vec2 hitPoint) { return Item::heal_formula(me, target, this); };
}