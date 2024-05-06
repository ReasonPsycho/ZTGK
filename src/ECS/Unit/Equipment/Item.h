//
// Created by igork on 25.03.2024.
//

#ifndef ITEM_H
#define ITEM_H
#include <string>
#include "Modifiers.h"
#include "GridRange.h"

struct ItemStats {
    float dmg{0};
    float cd_max_sec{1};
    GridRange range{};
    // ability

    Modifiers add_to_unit{};
};

class Item {
public:
    unsigned item_type_id;

    bool offensive{false};
    float cd_sec{0};

    std::string name;
    std::string description;
    ItemStats stats{};
    bool takesTwoSlots;

    Item(std::string name, std::string desctiption, bool offensive, ItemStats stats, bool takesTwoSlots = false);

    static Item default_attack_item();
};



#endif //ITEM_H
