//
// Created by cheily on 04.04.2024.
//

#pragma once

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "Utils/Util.h"
#include "ECS/Component.h"
#include "ECS/HUD/Fonts.h"

struct TextData {
    std::string content;
    std::string font;
    unsigned HUDGroupID = 0;
    glm::vec2 pos = { 200, 200 };
    glm::vec2 scale = { 1, 1 };
    glm::vec3 color = ztgk::color.WHITE;
    unsigned style = 0;
};

enum TextStyle {
    NONE            = 0,
    UNDERSCORE      = 1 << 0,
    STRIKETHROUGH   = 1 << 1,
    OVERLINE        = 1 << 2,
    BOX             = 1 << 3,

    // we are loading the basic ascii table of 128 chars, these values can directly work as array indexing offset for their effects
    ITALIC          = 1 << 7,   //128
    BOLD            = 1 << 8,   //256
};

class Text : public Component {
public:
    TextData data;

    // component overrides
    void showImGuiDetails(Camera *camera) override;
};
