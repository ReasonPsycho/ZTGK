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
class HUD;

struct Glyph {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;         // Size of glyph
    glm::ivec2 Bearing;      // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class TextRenderer {
public:
    explicit TextRenderer(HUD * hud);
    ~TextRenderer();

    HUD * hud;

    void loadFont(std::string font);
    void render(Text * text);
    [[nodiscard]] glm::vec2 size(Text * text) const;

    std::unordered_map<std::string, std::unordered_map<unsigned, Glyph>> fonts;

    // editor
    void imgui_controls();
private:
    unsigned VAO, VBO;

    glm::mat4 projection;
    FT_Library ft;

    Shader shader;

    glm::vec2 drawModeOffset(Text * text) const;
};
