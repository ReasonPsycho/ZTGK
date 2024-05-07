//
// Created by cheily on 07.05.2024.
//

#pragma once


#include "ECS/Unit/Equipment/Item.h"

class Hands : public Item {
public:
    Hands() : Item("Hands", "Even a sponge can throw hands!", true, {
        .dmg = 5,
        .cd_max_sec = 1,
        .range = GridRange(1),
        .add_to_unit = {}
    }) {}
};
