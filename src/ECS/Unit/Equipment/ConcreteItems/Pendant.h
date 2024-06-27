//
// Created by cheily on 24.06.2024.
//

#ifndef SCRUB_SQUAD_PENDANT_H
#define SCRUB_SQUAD_PENDANT_H


#include "ECS/Unit/Equipment/Item.h"

class Pendant : public Item {
public:
    Pendant() : Item(Item::item_types.pendant, "Pendant", "Sea Breeze. Now lasting 200 flushes!", false,
                      ItemStats(0,0,GridRange(0, 0), GridRange(0, 0), {/* RANDOM */}), false) {
        icon_path = "res/textures/icons/item_pendant.png";
        model = ztgk::game::kulki; // todo change model

        std::vector<ItemStats> random_stats = {
            ItemStats(
                0,0,GridRange(0, 0), GridRange(0, 0),
                {
                    .move_speed = 4
                }),
            ItemStats(
                0,0,GridRange(0, 0), GridRange(0, 0),
                {
                    .mine_speed = 0.5
                }),
            ItemStats(
                0,0,GridRange(0, 0), GridRange(0, 0),
                {
                    .move_speed = 2,
                    .mine_speed = 0.25
                }),
        };

        this->stats = random_stats[rand() % random_stats.size()];
        if (stats.add_to_unit.move_speed > 0.1)
            highlight_passive_stats.emplace("res/textures/icons/stat/mvspd.png", std::format("{:1.0}", std::to_string(stats.add_to_unit.move_speed)));
        if (stats.add_to_unit.def_perc > 0.1)
            highlight_passive_stats.emplace("res/textures/icons/stat/mnspd.png", std::format("{:.2}", std::to_string(stats.add_to_unit.mine_speed)));
    }

};

#endif //SCRUB_SQUAD_PENDANT_H
