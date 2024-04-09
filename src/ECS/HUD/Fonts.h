//
// Created by cheily on 07.04.2024.
//

#pragma once

#include <string>
#include <array>

namespace ztgk {

    struct FontFamily {
        std::string regular;
        std::string bold;
        std::string italic;
        std::string bold_italic;

        [[nodiscard]] std::string toString() const {
            return std::format("FontFamily{{regular='{}', bold='{}', italic='{}', bold_italic='{}'}}",
                               regular, bold, italic, bold_italic);
        }
    };

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

        [[nodiscard]] constexpr FontFamily family(const std::string & base) const {
            return { base + regular, base + bold, base + italic, base + bold_italic };
        }

        const std::string default_font = Fam_Lato + regular;
        const FontFamily default_family = family(Fam_Lato);
    } static font;


}