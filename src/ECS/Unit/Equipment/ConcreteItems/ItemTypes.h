//
// Created by cheily on 06.05.2024.
//

#pragma once

class Item;

struct s_item_types {
    unsigned hands;
    unsigned mop;
    unsigned water_gun;

    // add new type here!!
    s_item_types();
    // and here!!
    unsigned id_of(Item * item) const;
};