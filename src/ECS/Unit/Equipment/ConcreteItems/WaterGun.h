//
// Created by igork on 25.03.2024.
//

#ifndef WATERGUN_H
#define WATERGUN_H
#include "ECS/Unit/Equipment/Item.h"


class WaterGun : public Item{
public:
    WaterGun() : Item("Capsule Gun", "Works on 100% common stains.", true, ItemStats(15, 3, GridRange(3, 0), GridRange(2, 0)), true) {
        icon_path = "res/textures/icons/item_tidePodLauncher.png";
        model = ztgk::game::tideGun;

        determine_damage = [this](Unit * me, Unit * target, glm::vec2 hitPoint) { return Item::aoe_explosion_formula(me, target, this, hitPoint); };
        do_attack = [this](Unit * me, Unit * target) { Item::do_ranged_aoe_attack(me, target, this); };
    }
};



#endif //WATERGUN_H
