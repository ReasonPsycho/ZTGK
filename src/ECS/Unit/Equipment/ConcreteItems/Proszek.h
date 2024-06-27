//
// Created by cheily on 26.06.2024.
//

#ifndef SCRUB_SQUAD_PROSZEK_H
#define SCRUB_SQUAD_PROSZEK_H

#include "ECS/Unit/Equipment/Item.h"

class Proszek : public Item {
public:
    Proszek() : Item(Item::item_types.proszek, "Proszek", "sypki", false,
                      ItemStats(0,0,GridRange(0, 0), GridRange(0, 0),
                              {/* RANDOM */}), false) {
        icon_path = "res/textures/icons/item_powder.png";
        model = ztgk::game::proszek; // todo change model

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
        if (stats.add_to_unit.max_hp > 0.1)
            highlight_passive_stats.emplace("res/textures/icons/stat/hp.png", std::format("{:1.0f}", (stats.add_to_unit.max_hp)));
        if (stats.add_to_unit.def_perc > 0.1)
            highlight_passive_stats.emplace("res/textures/icons/stat/def.png", std::format("{:1.0f}%", (stats.add_to_unit.def_perc * 100)));
        if (stats.add_to_unit.def_flat > 0.1)
            highlight_passive_stats.emplace("res/textures/icons/stat/def.png", std::format("{:1.0f}", (stats.add_to_unit.def_flat)));
        if (stats.add_to_unit.move_speed > 0.1)
            highlight_passive_stats.emplace("res/textures/icons/stat/mvspd.png", std::format("{:1.0f}", (stats.add_to_unit.move_speed)));
        if (stats.add_to_unit.mine_speed > 0.1)
            highlight_passive_stats.emplace("res/textures/icons/stat/mnspd.png", std::format("{:1.0f}%", (stats.add_to_unit.mine_speed * 100)));
    }

};

#endif //SCRUB_SQUAD_PROSZEK_H
