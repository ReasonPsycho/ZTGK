//
// Created by igork on 25.03.2024.
//

#ifndef WATERGUN_H
#define WATERGUN_H
#include "ECS/Unit/Equipment/Item.h"


class WaterGun : public Item{
public:
    WaterGun() : Item("Water Gun", "A water gun to clean the floor", true, ItemStats(10, 2, GridRange(3, 0), GridRange(1, 0)), true) {
        icon_path = "res/textures/icons/item_tidePodLauncher.png";
        model = ztgk::game::tidyPodLauncherModel;

        determine_damage = [this](Unit * me, Unit * target, glm::vec2 hitPoint) { return Item::aoe_explosion_formula(me, target, this, hitPoint); };
        do_attack = [this](Unit * me, Unit * target) { Item::do_ranged_aoe_attack(me, target, this); };
    }
};



#endif //WATERGUN_H
