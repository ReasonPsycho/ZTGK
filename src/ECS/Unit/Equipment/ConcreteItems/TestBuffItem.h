//
// Created by cheily on 13.05.2024.
//

#pragma once

#include "ECS/Unit/Equipment/Item.h"

class TestBuffItem : public Item {
public:
    TestBuffItem() : Item("TestBuffItem", "None", false, {
        .add_to_unit = {
                .max_hp = 10,
                .def_perc = 5,
                .def_flat = 1,
                .move_speed = 1,
                .mine_speed = 0.3,
                .dmg_perc = 0.5,
                .dmg_flat = 100,
                .rng_add = 3,
                .rng_rem = 1,
                .atk_speed = 0.3,
                .knockback = 1
        }
    }) {
        icon_path = "res/textures/pranium.png";
        highlight_passive_stats = {
                {"DMG", "100"},
                {"DMG%", "0.5"},
                {"ASPD", "0.3"}
        };
    }
};
