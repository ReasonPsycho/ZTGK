//
// Created by cheily on 04.04.2024.
//

#include "Text.h"

Text::Text(const std::string &content, const glm::vec2 &pos, const glm::vec2 &scale, const glm::vec4 &color,
           const std::string &font, TextStyle style, unsigned int hudGroupId)
: AHUDComponent(TEXT, hudGroupId), content(content), pos(pos), scale(scale), color(color), font(font), style(style) {
    name = "Text: " + content;
}

void Text::showImGuiDetails(Camera *camera) {
    ImGui::DragFloat2("Pos", glm::value_ptr(pos));
    ImGui::DragFloat2("Scale", glm::value_ptr(scale), 0.01);
    ImGui::ColorEdit4("Color", glm::value_ptr(color));
    char c[100];
    strcpy_s(c, content.c_str());
    ImGui::InputText("Content", c, 100);
    content = c;
}
