//
// Created by cheily on 04.05.2024.
//

#pragma once

#include "imgui.h"

struct Modifiers {
    // unit-base
    float max_hp{0};
    float def_perc{0};
    float def_flat{0};
    float move_speed{0};
    float mine_speed{0};
    // item-base
    float dmg_perc{0};
    float dmg_flat{0};
    int rng_add{0};
    int rng_rem{0};
    float atk_speed{0};
    int knockback{0};
    
    Modifiers & operator+=(Modifiers & rhs) {
        max_hp += rhs.max_hp;
        def_perc += rhs.def_perc;
        def_flat += rhs.def_flat;
        move_speed += rhs.move_speed;
        mine_speed += rhs.mine_speed;
        dmg_perc += rhs.dmg_perc;
        dmg_flat += rhs.dmg_flat;
        rng_add += rhs.rng_add;
        rng_rem += rhs.rng_rem;
        atk_speed += rhs.atk_speed;
        knockback += rhs.knockback;
        return *this;
    }
    
    Modifiers & operator-=(Modifiers & rhs) {
        max_hp -= rhs.max_hp;
        def_perc -= rhs.def_perc;
        def_flat -= rhs.def_flat;
        move_speed -= rhs.move_speed;
        mine_speed -= rhs.mine_speed;
        dmg_perc -= rhs.dmg_perc;
        dmg_flat -= rhs.dmg_flat;
        rng_add -= rhs.rng_add;
        rng_rem -= rhs.rng_rem;
        atk_speed -= rhs.atk_speed;
        knockback -= rhs.knockback;
        return *this;
    }

    void imgui_preview() const {
        ImGui::Text("Max HP: %f", max_hp);
        ImGui::Text("Def %%: %f", def_perc);
        ImGui::Text("Def flat: %f", def_flat);
        ImGui::Text("Move SPD: %f", move_speed);
        ImGui::Text("Mine SPD: %f", mine_speed);
        ImGui::Text("Dmg %%: %f", dmg_perc);
        ImGui::Text("Dmg flat: %f", dmg_flat);
        ImGui::Text("Range +: %d", rng_add);
        ImGui::Text("Range -: %d", rng_rem);
        ImGui::Text("Atk SPD: %f", atk_speed);
        ImGui::Text("Knockback: %d", knockback);
    }
};
