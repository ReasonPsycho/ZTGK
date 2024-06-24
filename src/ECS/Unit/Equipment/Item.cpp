//
// Created by igork on 25.03.2024.
//

#include "Item.h"
#include "ECS/Utils/Util.h"
#include "ECS/Unit/Unit.h"
#include "ECS/Render/Components/AnimationPlayer.h"
#include "ECS/Unit/UnitAI/StateMachine/States/CombatState.h"
#include "ECS/Unit/Equipment/Projectile/Projectile.h"

const s_item_types Item::item_types{};

Item::Item(std::string name, std::string description, bool offensive, ItemStats stats, bool takesTwoSlots, Model * model)
    : uniqueID(ztgk::id<ztgk::ID_POOL_ITEM>()), name(name), description(description), offensive(offensive), stats(stats), takesTwoSlots(takesTwoSlots), model(model) {

    // default impls, for hands
    determine_damage = [this](Unit * me, Unit * target, glm::vec2 explosionPoint) { return Item::default_damage_formula(me, target, this); };
    do_attack = [this](Unit * me, Unit * target) { Item::do_meele_attack(me, target, this); };
    determine_target = [this](Unit * me) { return default_determine_target(me, me->equipment.range_of(this)); };

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
    float totalAttackDamage = usedItem->determine_damage(me, target, VectorUtils::Vector2IntToGlmVec2(target->gridPosition));

    CombatState::applyDamage(me, target, totalAttackDamage);
}

void Item::do_meele_aoe_attack(Unit *me, Unit *target, Item *usedItem) {
    auto targets = usedItem->stats.aoe_range.find_my_enemies({target->gridPosition.x, target->gridPosition.z}, me->IsAlly());

    for (auto & tgt : targets) {
        float totalAttackDamage = usedItem->determine_damage(me, tgt, {target->gridPosition.x, target->gridPosition.z}); // hit point here is explosion center so original target position
        CombatState::applyDamage(me, tgt, totalAttackDamage);
    }
}

void Item::do_ranged_attack(Unit *me, Unit *target, Item *usedItem) {
    float totalAttackDamage = usedItem->determine_damage(me, target, VectorUtils::Vector2IntToGlmVec2(target->gridPosition));

    auto projectileEntity = ztgk::game::scene->addEntity("Projectile");
    projectileEntity->transform.setLocalPosition(me->worldPosition);
    projectileEntity->addComponent(std::make_unique<Render>(ztgk::game::projectileModel));
    projectileEntity->addComponent(std::make_unique<Projectile>(me->worldPosition,  target->worldPosition, me, target, usedItem, totalAttackDamage));
    projectileEntity->transform.setLocalScale({0.1f, 0.1f, 0.1f});
    projectileEntity->updateSelfAndChild();
}

void Item::do_ranged_aoe_attack(Unit *me, Unit *target, Item *usedItem) {
    float totalAttackDamage = usedItem->determine_damage(me, target, VectorUtils::Vector2IntToGlmVec2(target->gridPosition));

    auto projectileEntity = ztgk::game::scene->addEntity("Projectile");
    projectileEntity->transform.setLocalPosition(me->worldPosition);
    projectileEntity->addComponent(std::make_unique<Render>(ztgk::game::projectileModel));
    projectileEntity->addComponent(std::make_unique<Projectile>(me->worldPosition,  target->worldPosition, me, target, usedItem, totalAttackDamage));
    projectileEntity->transform.setLocalScale({0.1f, 0.1f, 0.1f});
    projectileEntity->updateSelfAndChild();
    auto projectile = projectileEntity->getComponent<Projectile>();
    projectile->onHit = [projectile]() -> std::vector<Unit *> {
        auto targets = projectile->sourceItem->stats.aoe_range.find_my_enemies({projectile->target->gridPosition.x, projectile->target->gridPosition.z}, projectile->unit->IsAlly());
        for (auto & tgt : targets) {
            float totalAttackDamage = projectile->sourceItem->determine_damage(projectile->unit, tgt, {projectile->target->gridPosition.x, projectile->target->gridPosition.z}); // hit point here is explosion center so original target position
            CombatState::applyDamage(projectile->unit, tgt, totalAttackDamage);
        }
        return targets;
    };
}

void Item::do_heal(Unit *me, Unit *target, Item *usedItem) {
    auto targets = usedItem->stats.aoe_range.find_my_allies({target->gridPosition.x, target->gridPosition.z}, me->IsAlly());

    for (auto & tgt : targets) {
        float totalHealAmount = usedItem->determine_damage(me, tgt, {me->gridPosition.x, me->gridPosition.z}); // hit point here is explosion center so original ME position - this is for beacon centered on unit
        CombatState::applyDamage(me, tgt, totalHealAmount);
    }
}

Unit *Item::default_determine_target(Unit *me, GridRange * range) {
    std::vector<Unit *> sorted = {};
    sorted = range->find_my_enemies({me->gridPosition.x, me->gridPosition.z}, me->IsAlly());
    std::sort(sorted.begin(), sorted.end(), [me](Unit * a, Unit * b) {
        return VectorUtils::GridDistance(me->gridPosition, a->gridPosition) < VectorUtils::GridDistance(me->gridPosition, b->gridPosition);
    });
    return sorted.empty() ? nullptr : sorted.at(0);
}

Unit *Item::determine_healing_target(Unit *me, GridRange *range) {
    std::vector<Unit *> sorted = {};
    sorted = range->find_my_allies({me->gridPosition.x, me->gridPosition.z}, me->IsAlly())
            | std::views::filter([](Unit * u) { return u->stats.hp < u->stats.max_hp + u->stats.added.max_hp; })
            | std::ranges::to<std::vector<Unit*>>();
    std::sort(sorted.begin(), sorted.end(), [me](Unit * a, Unit * b) {
        return VectorUtils::GridDistance(me->gridPosition, a->gridPosition) < VectorUtils::GridDistance(me->gridPosition, b->gridPosition);
    });

    return sorted.empty() ? nullptr : sorted.at(0);
}
