//
// Created by cheily on 04.04.2024.
//

#include "Text.h"
#include "ECS/SignalQueue/SignalQueue.h"
#include "ECS/SignalQueue/DataCargo/EditorSignals/HUD/HUDRemapGroupsSignalData.h"

Text::Text(const std::string &content, const glm::vec2 &pos, const glm::vec2 &scale, const glm::vec4 &color,
           const std::string &font, TextStyle style, unsigned int hudGroupId)
: AHUDComponent(TEXT, hudGroupId), content(content), scale(scale), color(color), font(font), style(style) {
    AHUDComponent::pos = pos;
    name = std::format("Text: {}###{}", content, uniqueID);
    strcpy_s(editor_content_buffer, content.c_str());
    strcpy_s(editor_font_buffer, font.c_str());
}

void Text::showImGuiDetailsImpl(Camera *camera) {
    ImGui::DragFloat2("Pos", glm::value_ptr(pos));
    ImGui::DragFloat2("Scale", glm::value_ptr(scale), 0.01);
    ImGui::ColorEdit4("Color", glm::value_ptr(color));
    ImGui::InputText("Content", editor_content_buffer, 100);
    if ( content != editor_content_buffer ) {
        content = editor_content_buffer;
        name = std::format("Text: {}###{}", content, uniqueID);
    }
    static unsigned gid;
    gid = groupID;
    ImGui::InputInt("Group ID", reinterpret_cast<int *>(&groupID));
    if (gid != groupID) {
        *ztgk::game::scene->systemManager.getSystem<SignalQueue>() += HUDRemapGroupsSignalData::signal(
            false, uniqueID, type, gid, groupID, "Editor event."
        );
        groupID = gid;
    }
    static const char * const modes[] = MODE_NAMES;
    ImGui::Combo("Draw Mode", reinterpret_cast<int *>(&mode), modes, num_modes);

    ImGui::Text("Font");

    ImGui::InputText("Path", editor_font_buffer, editor_buffer_size);
    ImGui::SameLine();
    if (ImGui::Button("Load")) {
        font = editor_font_buffer;
    }
    if (ImGui::Button("Regular")) {
        auto s = font.substr(0, font.find_last_of('-') + 1);
        s += ztgk::font.regular;
        strcpy_s(editor_font_buffer, s.c_str());
        font = s;
    }
    ImGui::SameLine();
    if (ImGui::Button("Bold")) {
        auto s = font.substr(0, font.find_last_of('-') + 1);
        s += ztgk::font.bold;
        strcpy_s(editor_font_buffer, s.c_str());
        font = s;
    }
    ImGui::SameLine();
        if (ImGui::Button("Italic")) {
        auto s = font.substr(0, font.find_last_of('-') + 1);
        s += ztgk::font.italic;
        strcpy_s(editor_font_buffer, s.c_str());
        font = s;
    }
    ImGui::SameLine();
    if (ImGui::Button("Bold Italic")) {
        auto s = font.substr(0, font.find_last_of('-') + 1);
        s += ztgk::font.bold_italic;
        strcpy_s(editor_font_buffer, s.c_str());
        font = s;
    }

    if(ImGui::BeginCombo("Preset", font.c_str())) {
        for ( auto preset : ztgk::font.all_presets() ) {
            ImGui::PushID(preset.c_str());
            if (ImGui::Selectable(preset.substr(preset.find_last_of('/') + 1).c_str(), font == preset)) {
                font = preset;
                strcpy_s(editor_font_buffer, preset.c_str());
            }
            ImGui::PopID();
        }
        ImGui::EndCombo();
    }
}
