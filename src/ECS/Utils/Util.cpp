//
// Created by cheily on 21.03.2024.
//

#include "Util.h"
#include "ECS/Unit/Unit.h"
#include "ECS/HUD/Components/Text.h"
#include "ECS/HUD/Components/Sprite.h"
#include "ECS/HUD/Interactables/HUDSlider.h"
#include "ECS/HUD/HUD.h"

namespace ztgk {

    long long time() {
        return std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::steady_clock::now().time_since_epoch()).count();
    }

    Console ztgk::console = Console();

    void update_unit_hud(Unit *unit) {
        auto eunit = ztgk::game::scene->getChild("HUD")->getChild("Game")->getChild("Unit Details");

        auto ent = eunit->getChild("Portrait");
        ent->getComponent<Sprite>()->load(unit->icon_path);

        ent = eunit->getChild("Name");
        ent->getComponent<Text>()->content = unit->name;

        auto emods = eunit->getChild("Mods");
        emods->getChild("ATK")->getComponent<Text>()->content = std::format("{} + {}", unit->stats.added.dmg_perc, unit->stats.added.dmg_flat);
        emods->getChild("DEF")->getComponent<Text>()->content = std::format("{} + {}", unit->stats.added.def_perc, unit->stats.added.def_flat);
        emods->getChild("CD")->getComponent<Text>()->content = std::format("{}", unit->stats.added.atk_speed);
        emods->getChild("RNG")->getComponent<Text>()->content = std::format("{}", unit->stats.added.rng_add);
        emods->getChild("MNSP")->getComponent<Text>()->content = std::format("{}", unit->stats.mine_spd + unit->stats.added.mine_speed);
        emods->getChild("MVSP")->getComponent<Text>()->content = std::format("{}", unit->stats.move_spd + unit->stats.added.move_speed);

        eunit->getChild("Display Bar")->getComponent<HUDSlider>()->displayMax = unit->stats.max_hp + unit->stats.added.max_hp;
        eunit->getChild("Display Bar")->getComponent<HUDSlider>()->set_in_display_range(unit->stats.hp);

        update_weapon_hud(unit);
    }

    void update_weapon_hud(Unit *unit) {
        if (unit->equipment.item1) {
            auto eitem1 = ztgk::game::scene->getChild("HUD")->getChild("Game")->getChild("Unit Details")->getChild("Weapon Portrait #1");
            eitem1->getComponent<Text>()->content = unit->equipment.item1->name;
            eitem1->getComponent<Sprite>()->load(unit->equipment.item1->icon_path);
            if (unit->equipment.item1->offensive) {
                ztgk::game::scene->systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_w1_offensive)->setHidden(false);
                ztgk::game::scene->systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_w1_passive)->setHidden(true);
    
                eitem1->getChild("Offensive Stats")->getChild("ATK")->getComponent<Text>()->content = std::format("{}",unit->equipment.item1->stats.dmg);
                eitem1->getChild("Offensive Stats")->getChild("RNG")->getComponent<Text>()->content = std::format("{}",unit->equipment.item1->stats.range.add);
                eitem1->getChild("Offensive Stats")->getChild("CD")->getChild("Display Bar")->getComponent<HUDSlider>()->displayMax = unit->equipment.item1->stats.cd_max_sec;
                eitem1->getChild("Offensive Stats")->getChild("CD")->getChild("Display Bar")->getComponent<HUDSlider>()->set_in_display_range(unit->equipment.item1->cd_sec);
            } else {
                ztgk::game::scene->systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_w1_offensive)->setHidden(true);
                ztgk::game::scene->systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_w1_passive)->setHidden(false);
    
                auto ent = eitem1->getChild("Passive Stats");
                int i = 1;
                for (auto stats : unit->equipment.item1->highlight_passive_stats) {
                    string ent_name = "STAT" + to_string(i);
                    ent->getChild(ent_name)->getChild("Button - " + ent_name)->getComponent<Text>()->content = stats.first;
                    ent->getChild(ent_name)->getComponent<Text>()->content = stats.second;
                    i++;
                }
            }
        } else {
            auto eitem1 = ztgk::game::scene->getChild("HUD")->getChild("Game")->getChild("Unit Details")->getChild("Weapon Portrait #1");
            eitem1->getComponent<Text>()->content = "*No Item*";
            eitem1->getComponent<Sprite>()->load("res/textures/question_mark.png");
            ztgk::game::scene->systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_w1_offensive)->setHidden(true);
            ztgk::game::scene->systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_w1_passive)->setHidden(true);
        }
    
        if (unit->equipment.item2) {
            auto eitem2 = ztgk::game::scene->getChild("HUD")->getChild("Game")->getChild("Unit Details")->getChild("Weapon Portrait #2");
            eitem2->getComponent<Text>()->content = unit->equipment.item2->name;
            eitem2->getComponent<Sprite>()->load(unit->equipment.item2->icon_path);
            if (unit->equipment.item2->offensive) {
                ztgk::game::scene->systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_w2_offensive)->setHidden(false);
                ztgk::game::scene->systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_w2_passive)->setHidden(true);
    
                eitem2->getChild("Offensive Stats")->getChild("ATK")->getComponent<Text>()->content = std::format("{}",unit->equipment.item2->stats.dmg);
                eitem2->getChild("Offensive Stats")->getChild("RNG")->getComponent<Text>()->content = std::format("{}",unit->equipment.item2->stats.range.add);
                eitem2->getChild("Offensive Stats")->getChild("CD")->getChild("Display Bar")->getComponent<HUDSlider>()->displayMax = unit->equipment.item2->stats.cd_max_sec;
                eitem2->getChild("Offensive Stats")->getChild("CD")->getChild("Display Bar")->getComponent<HUDSlider>()->set_in_display_range(unit->equipment.item2->cd_sec);
            } else {
                ztgk::game::scene->systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_w2_offensive)->setHidden(true);
                ztgk::game::scene->systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_w2_passive)->setHidden(false);
    
                auto ent = eitem2->getChild("Passive Stats");
                int i = 1;
                for (auto stats : unit->equipment.item2->highlight_passive_stats) {
                    string ent_name = "STAT" + to_string(i);
                    ent->getChild(ent_name)->getChild("Button - " + ent_name)->getComponent<Text>()->content = stats.first;
                    ent->getChild(ent_name)->getComponent<Text>()->content = stats.second;
                    i++;
                }
            }
        } else {
            auto eitem2 = ztgk::game::scene->getChild("HUD")->getChild("Game")->getChild("Unit Details")->getChild("Weapon Portrait #2");
            eitem2->getComponent<Text>()->content = "*No Item*";
            eitem2->getComponent<Sprite>()->load("res/textures/question_mark.png");
            ztgk::game::scene->systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_w2_offensive)->setHidden(true);
            ztgk::game::scene->systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_w2_passive)->setHidden(true);
        }
    
        if (!unit->equipment.item1 && !unit->equipment.item2) {
            auto eitem0 = ztgk::game::scene->getChild("HUD")->getChild("Game")->getChild("Unit Details")->getChild("Weapon Portrait #1");
            eitem0->getComponent<Text>()->content = unit->equipment.item0->name + " - No Item";
            eitem0->getComponent<Sprite>()->load(unit->equipment.item0->icon_path);
            if (unit->equipment.item0->offensive) {
                ztgk::game::scene->systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_w1_offensive)->setHidden(false);
                ztgk::game::scene->systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_w1_passive)->setHidden(true);
    
                eitem0->getChild("Offensive Stats")->getChild("ATK")->getComponent<Text>()->content = std::format("{}",unit->equipment.item0->stats.dmg);
                eitem0->getChild("Offensive Stats")->getChild("RNG")->getComponent<Text>()->content = std::format("{}",unit->equipment.item0->stats.range.add);
                eitem0->getChild("Offensive Stats")->getChild("CD")->getChild("Display Bar")->getComponent<HUDSlider>()->displayMax = unit->equipment.item0->stats.cd_max_sec;
                eitem0->getChild("Offensive Stats")->getChild("CD")->getChild("Display Bar")->getComponent<HUDSlider>()->set_in_display_range(unit->equipment.item0->cd_sec);
            }
        }
    }
}