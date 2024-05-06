//
// Created by igork on 25.03.2024.
//

#include "Item.h"

Item::Item(std::string name, std::string desctiption, bool offensive, ItemStats stats, bool takesTwoSlots)
    : name(name), description(desctiption), offensive(offensive), stats(stats), takesTwoSlots(takesTwoSlots) {
}

Item Item::default_attack_item() {
    return Item("Just hands", "Even sponges can throw hands.", true, ItemStats{
        .dmg = 5,
        .cd_max_sec = 2,
        .range = GridRange(1),
        .add_to_unit = {}
    });
}
