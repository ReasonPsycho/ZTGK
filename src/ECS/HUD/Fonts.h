// 
// Created by cheily on 07.04.2024. 
// 
 
#pragma once 
 
#include <string> 
#include <array> 
 
namespace ztgk { 
 
    struct s_font { 
        // variants, use as default 
        const std::string Fam_Lato = "res/fonts/Lato/Lato-"; 
        const std::string Fam_Arimo = "res/fonts/Arimo/static/Arimo-"; 
        const std::string Fam_Nunito = "res/fonts/Nunito/static/Nunito-"; 
 
        const std::string Reg_Quicksand = "res/fonts/Quicksand/static/Quicksand-Regular.ttf"; 
        const std::string Bld_Quicksand = "res/fonts/Quicksand/static/Quicksand-Bold.ttf"; 
 
        // regular-only 
        const std::string Reg_Lobster = "res/fonts/Lobster/Lobster-Regular.ttf"; 
        const std::string Reg_Concert = "res/fonts/Concert_One/ConcertOne-Regular.ttf"; 
        const std::string Reg_NovaMono = "res/fonts/Nova_Mono/NovaMono-Regular.ttf"; 
 
        const std::string regular = "Regular.ttf"; 
        const std::string italic = "Italic.ttf"; 
        const std::string bold = "Bold.ttf"; 
        const std::string bold_italic = "BoldItalic.ttf"; 
 
        const std::string default_font = Fam_Lato + regular; 
 
        [[nodiscard]] constexpr std::vector<std::string> all_presets() const { 
            std::vector<std::string> ret = {}; 
 
            for ( auto & fam : { Fam_Lato, Fam_Arimo, Fam_Nunito } ) { 
                ret.push_back(fam + regular); 
                ret.push_back(fam + bold); 
                ret.push_back(fam + italic); 
                ret.push_back(fam + bold_italic); 
            } 
            ret.push_back(Reg_Quicksand); 
            ret.push_back(Bld_Quicksand); 
            ret.push_back(Reg_Lobster); 
            ret.push_back(Reg_Concert); 
            ret.push_back(Reg_NovaMono); 
 
            return ret; 
        } 
    } static font; 
} 
