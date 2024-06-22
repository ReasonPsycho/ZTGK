//
// Created by igork on 25.03.2024.
//

#include "Item.h"
#include "ECS/Utils/Util.h"
#include "ECS/Unit/Unit.h"

const s_item_types Item::item_types{};

Item::Item(std::string name, std::string description, bool offensive, ItemStats stats, bool takesTwoSlots, Model * model)
    : uniqueID(ztgk::id<ztgk::ID_POOL_ITEM>()), name(name), description(description), offensive(offensive), stats(stats), takesTwoSlots(takesTwoSlots), model(model) {

    // default impls, for hands
    determine_damage = [this](Unit * me, Unit * target, glm::vec2 explosionPoint) { return Item::default_damage_formula(me, target, this); };
    do_attack = [this](Unit * me, Unit * target) { Item::do_meele_attack(me, target, this); };
    determine_target = [](const GridRange & range, glm::ivec2 center) {
        return GridRange::f_find_dirts_in_range_sorted(range, center).at(0);
    };

}

void Item::imgui_preview() const {
    ImGui::Text("Description: %s", description.c_str());
    ImGui::Text("Offensive?: %d", offensive);
    ImGui::Text("2 slot?: %d", takesTwoSlots);
    ImGui::Text("CD (sec): %f / %f", cd_sec, stats.cd_max_sec);

    ImGui::Text("Raw Stats:");
    ImGui::Indent();
        ImGui::Text("Damage: %f", stats.dmg);
        ImGui::Text("CD max (sec): %f", stats.cd_max_sec);
        stats.range.imgui_preview();
    ImGui::Unindent();

    ImGui::Text("Raw Modifiers:");
    ImGui::Indent();
        stats.add_to_unit.imgui_preview();
    ImGui::Unindent();
}



float Item::default_damage_formula(Unit *me, Unit *target, Item *usedItem) {
    float totalAttackDamage =
        (usedItem->stats.dmg + usedItem->stats.dmg * me->stats.added.dmg_perc + me->stats.added.dmg_flat)
        * (1 - target->stats.added.def_perc) - target->stats.added.def_flat;
    return std::max(totalAttackDamage, 0.0f);
}

float Item::aoe_explosion_formula(Unit *me, Unit *target, Item *usedItem, glm::vec2 explosionPoint) {
    int dist = VectorUtils::GridDistance(VectorUtils::GlmVec2ToVector2Int(explosionPoint), target->gridPosition);
    int maxDist = me->equipment.range_of(usedItem)->add;
    int minDist = me->equipment.range_of(usedItem)->remove;
    float multiplier = 1.0f * dist / (maxDist - minDist); // map distance to 0-1 where 1 is max
    multiplier *= 0.5f; // scale to 0 - 0.5
    multiplier -= 0.5f; // move to -0.5 - 0
    multiplier *= -1; // flip so that max dist is @ 0, min dist @ 0.5
    multiplier += 0.5f; // move up to 0.5 - 1

    return multiplier * default_damage_formula(me, target, usedItem);
}

float Item::heal_formula(Unit *me, Unit *target, Item *usedItem) {
    float healAmount = usedItem->stats.dmg + usedItem->stats.dmg * me->stats.added.dmg_perc + me->stats.added.dmg_flat;
    return std::min(-healAmount, 0.0f);
}


void Item::do_meele_attack(Unit *me, Unit *target, Item *usedItem) {

}

void Item::do_meele_aoe_attack(Unit *me, Unit *target, Item *usedItem) {

}

void Item::do_ranged_attack(Unit *me, Unit *target, Item *usedItem) {

}

void Item::do_ranged_aoe_attack(Unit *me, Unit *target, Item *usedItem) {

}

void Item::do_heal(Unit *me, Unit *target, Item *usedItem) {

}
