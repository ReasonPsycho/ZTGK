//
// Created by cheily on 06.05.2024.
//

#pragma once

#include <unordered_map>
#include <string>

class Item;

struct s_item_types {
    unsigned hands;
    unsigned mop;
    unsigned super_mop;
    unsigned water_gun;
    unsigned beacon;
    unsigned test_buff_item;
    unsigned detergent;
    unsigned pendant;
    unsigned pranium_ore;
    unsigned proszek;

    std::unordered_map<unsigned, std::string> map;

    // add new type here too!!
    s_item_types();
    // and here!!
    [[nodiscard]] unsigned id_of(Item * item) const;
    [[nodiscard]] std::string types_string() const;
};