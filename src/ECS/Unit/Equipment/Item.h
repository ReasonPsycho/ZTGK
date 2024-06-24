//
// Created by igork on 25.03.2024.
//

#ifndef ITEM_H
#define ITEM_H
#include <string>
#include "Modifiers.h"
#include "GridRange.h"
#include "ConcreteItems/ItemTypes.h"

struct ItemStats {
    float dmg{0};
    float cd_max_sec{1};
    GridRange range{};
    GridRange aoe_range{};
    // ability

    Modifiers add_to_unit{};
};

class Item {
public:
    static const s_item_types item_types;

    unsigned uniqueID;

    bool offensive{false};
    float cd_sec{0};

    // bool on_ground{false};
    // glm::vec2 worldPos{};

    std::string name;
    std::string icon_path = "res/textures/question_mark.png";
    std::string description;
    ItemStats stats{};
    bool takesTwoSlots;
    Model * model;
    static inline const std::string ally_attack_animation_path = "res/models/gabka/pan_gabka_attack.fbx";
    static inline const std::string enemy_attack_animation_path = "";

// behavior implementations
    static void do_meele_attack(Unit * me, Unit * target, Item * usedItem);
    static void do_meele_aoe_attack(Unit * me, Unit * target, Item * usedItem);
    static void do_ranged_attack(Unit * me, Unit * target, Item * usedItem);
    static void do_ranged_aoe_attack(Unit * me, Unit * target, Item * usedItem);
    static void do_heal(Unit * me, Unit * target, Item * usedItem);

    static Unit * default_determine_target(Unit * me, GridRange * range, bool findAlly = false);
    static void play_atk_anim(Unit * me);

// damage formulas
    static float default_damage_formula(Unit * me, Unit * target, Item * usedItem);
    static float aoe_explosion_formula(Unit * me, Unit * target, Item * usedItem, glm::vec2 explosionPoint);
    static float heal_formula(Unit * me, Unit * target, Item * usedItem);

// behavior references
    std::function<Unit *(Unit * me)> determine_target;
    std::function<void(Unit * me, Unit * target)> do_attack;
    std::function<float(Unit * me, Unit * target, glm::vec2 hitPoint)> determine_damage;

    std::unordered_map<std::string, std::string> highlight_passive_stats = {};

    Item(std::string name, std::string description, bool offensive, ItemStats stats, bool takesTwoSlots = false, Model * model = ztgk::game::mopModel);

    void imgui_preview() const;
};



#endif //ITEM_H
