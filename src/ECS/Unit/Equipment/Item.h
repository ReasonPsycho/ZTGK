//
// Created by igork on 25.03.2024.
//

#ifndef ITEM_H
#define ITEM_H
#include <string>

struct ItemStats {
    float addHealth;
    float addAttackDamage;
    float addAttackSpeed;
    float addMovementSpeed;
    float addRange;

    ItemStats() = default;
    ItemStats(float addHealth, float addAttackDamage, float addAttackSpeed, float addMovementSpeed, float addRange) {
        this->addHealth = addHealth;
        this->addAttackDamage = addAttackDamage;
        this->addAttackSpeed = addAttackSpeed;
        this->addMovementSpeed = addMovementSpeed;
        this->addRange = addRange;
    }
};

class Item {
public:
    std::string name;
    std::string desctiption;
    ItemStats stats{};
    bool takesTwoSlots;

    Item(std::string name, std::string desctiption, ItemStats stats, bool takesTwoSlots = false);

};



#endif //ITEM_H
