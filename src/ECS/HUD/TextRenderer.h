//
// Created by cheily on 04.04.2024.
//

#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>
#include "glm/vec3.hpp"
#include "glm/fwd.hpp"
#include "glm/detail/type_vec2.hpp"
#include "glm/detail/type_mat4x4.hpp"
#include "ECS/Render/ModelLoading/Shader.h"
#include "ECS/HUD/Components/Text.h"
#include "Fonts.h"

struct Glyph {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class TextRenderer {
public:
    explicit TextRenderer(const ztgk::FontFamily & fontFamily = ztgk::font.default_font);

    const ztgk::FontFamily font_family = ztgk::font.family(ztgk::font.Fam_Arimo);

    unsigned VAO, VBO;
    glm::mat4 projection;
    std::unordered_map<unsigned short, Glyph> glyphs;

    FT_Library ft;
    std::unordered_map<std::string, std::unordered_map<unsigned, Glyph>> fonts;

    Shader shader;

    void loadFont(std::string font);

    void setFont(const ztgk::FontFamily & path);
    void render(TextData text);

private:
    void loadGlyphs(FT_Library ft, std::string face_path, int offset = 0);
};
