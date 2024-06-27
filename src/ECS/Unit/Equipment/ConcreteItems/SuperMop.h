//
// Created by cheily on 24.06.2024.
//

#ifndef SCRUB_SQUAD_SUPERMOP_H
#define SCRUB_SQUAD_SUPERMOP_H

#include "ECS/Unit/Equipment/Item.h"


class SuperMop : public Item{
public:
    SuperMop() : Item(Item::item_types.super_mop, "Rotary Mop", "With a blast!", true, ItemStats(10, 1.25, GridRange(1, 0), GridRange(1, 0)), false) {
        icon_path = "res/textures/icons/item_superMop.png";
        model = ztgk::game::mopObrotowyModel;

        do_attack = [this](Unit * me, Unit * target){ Item::do_meele_aoe_attack(me, target, this); };
        determine_damage = [this](Unit * me, Unit * target, glm::vec2 hitPoint) { return Item::aoe_explosion_formula(me, target, this, hitPoint); };
    }

};

#endif //SCRUB_SQUAD_SUPERMOP_H
