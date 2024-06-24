//
// Created by cheily on 24.06.2024.
//

#ifndef SCRUB_SQUAD_BEACON_H
#define SCRUB_SQUAD_BEACON_H

#include "ECS/Unit/Equipment/Item.h"

class Beacon : public Item {
public:
    Beacon() : Item("Soap Refill", "Refresh for the bravest!", true, ItemStats(5, 10, GridRange(4, 0), GridRange(0, 0)), true) {
        icon_path = "res/textures/icons/item_beacon.png";
        model = ztgk::game::tidyPodLauncherModel; // todo change model

        do_attack = [this](Unit * me, Unit * target){ Item::do_heal(me, target, this); };
        determine_damage = [this](Unit * me, Unit * target, glm::vec2 hitPoint) { return Item::heal_formula(me, target, this); };
    }

};

#endif //SCRUB_SQUAD_BEACON_H
