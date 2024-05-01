//
// Created by cheily on 04.04.2024.
//

#include "TextRenderer.h"
#include "ECS/Utils/Globals.h"
#include "HUD.h"

using namespace ztgk;

TextRenderer::TextRenderer(HUD * hud) : hud(hud), shader("res/shaders/hud_text.vert", "res/shaders/hud_text.frag") {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    projection = glm::ortho(0.0f, (float)game::window_size.x, 0.0f, (float)game::window_size.y);
    shader.init();

    if (FT_Init_FreeType(&ft)) {
        spdlog::error("ERROR::FREETYPE: Could not init FreeType Library");
        return;
    }

    loadFont(ztgk::font.default_font);
}

void TextRenderer::loadFont(std::string font) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    std::unordered_map<unsigned int, Glyph> _glyphs;

    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face)) {
        spdlog::error(std::format("Failed to initialize FT_Face for font: \"{}\"", font));
        return;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);

    for (unsigned char c = 0; c < 128; c++) {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            spdlog::error(std::format("Failed to load glyph '{}' for font \"{}\"", c, font));
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Glyph character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
        };
        _glyphs.insert(std::pair<unsigned int, Glyph>(c, character));
    }

    FT_Done_Face(face);

    fonts[font] = _glyphs;
    spdlog::trace("Loaded font  " + font);
    glDisable(GL_BLEND);                                                                         
}

void TextRenderer::render(Text * text) {
    if ( !fonts.contains(text->font) )
        loadFont(text->font);
    glEnable(GL_BLEND);

    // activate corresponding render state
    shader.use();
    shader.setMatrix4("projection", false, glm::value_ptr(projection));
    shader.setVec4("textColor", text->color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    auto glyphs = fonts[text->font];
    float xpos, ypos, adv = 0;
    // iterate through all characters
    for (auto & c : text->content) {
        Glyph ch = glyphs[c];

        auto group = hud->getGroupOrDefault(text->groupID);
        xpos = text->pos.x + ch.Bearing.x * text->scale.x + group->offset.x + adv;
        ypos = text->pos.y - (ch.Size.y - ch.Bearing.y) * text->scale.y + group->offset.y;

        float w = ch.Size.x * text->scale.x;
        float h = ch.Size.y * text->scale.y;
        // UpdateImpl VBO for each character
        float vertices[6][4] = {
                xpos,     ypos + h, 0.0f, 0.0f,
                xpos,     ypos,     0.0f, 1.0f,
                xpos + w, ypos,     1.0f, 1.0f,

                xpos,     ypos + h, 0.0f, 0.0f,
                xpos + w, ypos,     1.0f, 1.0f,
                xpos + w, ypos + h, 1.0f, 0.0f
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // UpdateImpl content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        adv += (ch.Advance >> 6) * text->scale.x; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}

TextRenderer::~TextRenderer() {
    FT_Done_FreeType(ft);
}

void TextRenderer::imgui_controls() {
    ImGui::Text("%s", std::format("Shader ID: {}", shader.ID).c_str());
    ImGui::Text("Loaded fonts:");
    for ( auto & font : fonts ) {
        if ( ImGui::SmallButton(std::format("Reload##Reload{}", font.first).c_str()) ) {
            fonts.erase( font.first );
            // render() will automatically load the font back in
            return;
        }
        ImGui::SameLine();
        ImGui::Text("%s", font.first.c_str());
    }
}
