// 
// Created by cheily on 04.04.2024. 
// 
 
#pragma once 
 
#include "glm/vec2.hpp" 
#include "glm/vec3.hpp" 
#include "ECS/Utils/Util.h" 
#include "ECS/HUD/Fonts.h" 
#include "AHUDComponent.h" 
#include "ECS/Utils/Globals.h" 
 
enum TextStyle { 
    NONE            = 0, 
    UNDERSCORE      = 1 << 0, 
    STRIKETHROUGH   = 1 << 1, 
    OVERLINE        = 1 << 2, 
//    BOX             = 1 << 3, 
}; 
 
class Text : public AHUDComponent { 
public: 
//todo ctor 
    Text(const std::string &content = "", 
         const glm::vec2 &pos = ztgk::game::window_size / 2, 
         const glm::vec2 &scale = { 1, 1 }, 
         const glm::vec4 &color = ztgk::color.WHITE, 
         const std::string &font = ztgk::font.default_font, 
         TextStyle style = NONE, 
         unsigned int hudGroupId = 0); 
 
    std::string content; 
    std::string font; 
    glm::vec2 scale; 
    glm::vec4 color; 
    unsigned style; 
 
    // editor 
    static const unsigned editor_buffer_size = 100; 
    char editor_content_buffer[editor_buffer_size]; 
    char editor_font_buffer[editor_buffer_size]; 
    void showImGuiDetailsImpl(Camera *camera) override; 
}; 
