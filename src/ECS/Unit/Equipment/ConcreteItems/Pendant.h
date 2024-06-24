//
// Created by cheily on 24.06.2024.
//

#ifndef SCRUB_SQUAD_PENDANT_H
#define SCRUB_SQUAD_PENDANT_H


#include "ECS/Unit/Equipment/Item.h"

class Pendant : public Item {
public:
    Pendant() : Item("Pendant", "Sea Breeze. Now lasting 200 flushes!", false,
                      ItemStats(0,0,GridRange(0, 0), GridRange(0, 0)), false) {
        icon_path = "res/textures/icons/item_pendant.png";
        model = ztgk::game::tidyPodLauncherModel; // todo change model

        std::vector<ItemStats> random_stats = {
            ItemStats(
                0,0,GridRange(0, 0), GridRange(0, 0),
                {
                    .max_hp = 25
                }),
            ItemStats(
                0,0,GridRange(0, 0), GridRange(0, 0),
                {
                    .max_hp = 10,
                    .def_flat = 2
                }),
            ItemStats(
                0,0,GridRange(0, 0), GridRange(0, 0),
                {
                    .def_perc = 0.25
                }),
            ItemStats(
                0,0,GridRange(0, 0), GridRange(0, 0),
                {
                    .def_perc = 0.1,
                    .def_flat = 2
                }),
            ItemStats(
                0,0,GridRange(0, 0), GridRange(0, 0),
                {
                    .move_speed = 0.2,
                    .mine_speed = 0.4
                }),
        };

        this->stats = random_stats[rand() % random_stats.size()];
        if (stats.add_to_unit.max_hp != 0)
            highlight_passive_stats.insert({"res/textures/icons/stat/hp.png", std::to_string(stats.add_to_unit.max_hp)});
        if (stats.add_to_unit.def_perc != 0)
            highlight_passive_stats.insert({"res/textures/icons/stat/def.png", std::format("{:.0}%", stats.add_to_unit.def_perc * 100)});
        if (stats.add_to_unit.def_flat != 0)
            highlight_passive_stats.insert({"res/textures/icons/stat/def.png", std::to_string(stats.add_to_unit.def_flat)});
        if (stats.add_to_unit.move_speed != 0)
            highlight_passive_stats.insert({"res/textures/icons/stat/mvspd.png", std::format("{:.0}%", stats.add_to_unit.move_speed * 100)});
        if (stats.add_to_unit.mine_speed != 0)
            highlight_passive_stats.insert({"res/textures/icons/stat/mnspd.png", std::format("{:.0}%", stats.add_to_unit.mine_speed * 100)});
    }

};

#endif //SCRUB_SQUAD_PENDANT_H
