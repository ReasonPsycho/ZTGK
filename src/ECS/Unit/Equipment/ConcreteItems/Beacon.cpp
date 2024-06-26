//
// Created by cheily on 24.06.2024.
//
#include "ECS/Unit/Equipment/ConcreteItems/Beacon.h"
#include "ECS/Unit/Unit.h"

Beacon::Beacon() : Item(Item::item_types.beacon, "Soap Refill", "Refresh for the bravest!", false, ItemStats(10, 5, GridRange(4, 0), GridRange(0, 0)), true) {
    active = true;
    icon_path = "res/textures/icons/item_beacon.png";
    model = ztgk::game::healingo; // todo change model

    determine_target = [this](Unit * me) { return Item::determine_healing_target(me, me->equipment.range_of(this)); };
    do_attack = [this](Unit * me, Unit * target){ Item::do_heal(me, target, this); };
    determine_damage = [this](Unit * me, Unit * target, glm::vec2 hitPoint) { return Item::heal_formula(me, target, this); };

    highlight_passive_stats = {
        {"res/textures/icons/stat/hp.png", "5"},
        {"res/textures/icons/stat/rng.png", "4"}
    };
}