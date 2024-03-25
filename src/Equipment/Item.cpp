//
// Created by igork on 25.03.2024.
//

#include "Item.h"

Item::Item(std::string name, std::string desctiption, ItemStats stats, bool takesTwoSlots) {
    this->name = name;
    this->desctiption = desctiption;

    this->stats = ItemStats(stats.addHealth, stats.addAttackDamage, stats.addAttackSpeed, stats.addMovementSpeed, stats.addRange);
    this->takesTwoSlots = takesTwoSlots;

}