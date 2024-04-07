////
//// Created by cheily on 27.03.2024.
////
//
//#pragma once
//
////#include "spdlog/spdlog.h"
////#include "freetype-gl/freetype-gl.h"
////
//#include <ft2build.h>
//#include FT_FREETYPE_H
////#include "ECS/Render/ModelLoading/Shader.h"
//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL definitions
//#include <string>
//#include <unordered_map>
//#include "glm/vec3.hpp"
//#include "glm/fwd.hpp"
//#include "glm/detail/type_vec2.hpp"
//#include "glm/detail/type_mat4x4.hpp"
//#include "ECS/Render/ModelLoading/Shader.h"
////#include "freetype/freetype.h"
//
//struct Glyph {
//    unsigned int TextureID;  // ID handle of the glyph texture
//    glm::ivec2 Size;       // Size of glyph
//    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
//    unsigned int Advance;    // Offset to advance to next glyph
//};
//
//class TextRenderer {
//public:
//    FT_Library ft;
//    FT_Face face;
//
//    unsigned int VAO, VBO;
//    std::unordered_map<char, Glyph> characters;
//    glm::mat4 projection;
//
//    Shader shader;
//
//    bool init();
//
//    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
//
//    TextRenderer();
//};
