//
// Created by cheily on 24.06.2024.
//

#ifndef SCRUB_SQUAD_DETERGENT_H
#define SCRUB_SQUAD_DETERGENT_H

#include "ECS/Unit/Equipment/Item.h"

class Detergent : public Item {
public:
    Detergent() : Item("Gabka GO", "Extended power! Sparkling lemon!", false,
                      ItemStats(
                              0,0,GridRange(0, 0), GridRange(0, 0),
                              {/* RANDOM */}), false) {
        icon_path = "res/textures/icons/item_detergent.png";
        model = ztgk::game::superPlyn; // todo change model

        std::vector<ItemStats> random_stats = {
            ItemStats(
                0,0,GridRange(0, 0), GridRange(0, 0),
                {
                    .dmg_perc = 0.1,
                    .dmg_flat = 4
                }),
            ItemStats(
                0,0,GridRange(0, 0), GridRange(0, 0),
                {
                    .dmg_perc = 0.5,
                }),
            ItemStats(
                0,0,GridRange(0, 0), GridRange(0, 0),
                {
                    .dmg_perc = 0.25,
                    .atk_speed = 0.1
                }),
            ItemStats(
                0,0,GridRange(0, 0), GridRange(0, 0),
                {
                    .rng_add = 1,
                    .atk_speed = 0.1
                    //knockback instead of atk spd, if it ever works
                }),
            ItemStats(
                0,0,GridRange(0, 0), GridRange(0, 0),
                {
                    .atk_speed = 0.25
                }),
        };

        this->stats = random_stats[rand() % random_stats.size()];
        if (stats.add_to_unit.dmg_perc != 0)
            highlight_passive_stats.insert({"res/textures/icons/stat/atk.png", std::format("{:.0}%", stats.add_to_unit.dmg_perc * 100)});
        if (stats.add_to_unit.dmg_flat != 0)
            highlight_passive_stats.insert({"res/textures/icons/stat/atk.png", std::to_string(stats.add_to_unit.dmg_flat)});
        if (stats.add_to_unit.atk_speed != 0)
            highlight_passive_stats.insert({"res/textures/icons/stat/aspd.png", std::to_string(stats.add_to_unit.atk_speed)});
        if (stats.add_to_unit.rng_add != 0)
            highlight_passive_stats.insert({"res/textures/icons/stat/rng.png", std::to_string(stats.add_to_unit.rng_add)});
    }

};

#endif //SCRUB_SQUAD_DETERGENT_H
