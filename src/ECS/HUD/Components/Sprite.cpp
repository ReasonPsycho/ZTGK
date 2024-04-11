//
// Created by cheily on 04.04.2024.
//

#include <iostream>
#include <cstring>
#include "Sprite.h"
#include "imgui_impl_opengl3_loader.h"
#include "glad/glad.h"
#include "stb_image.h"
#include "ECS/SignalQueue/SignalQueue.h"
#include "ECS/SignalQueue/DataCargo/EditorSignals/HUD/HUDRemapGroupsSignalData.h"


Sprite::Sprite(const std::string &path)
: Sprite(ztgk::game::window_size / 2, {0, 0 }, ztgk::color.WHITE, 0, path)
{}

Sprite::Sprite(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color, unsigned int hudGroupId, const std::string &path)
: AHUDComponent(SPRITE, hudGroupId), pos(pos), size(size), color(color) {
    strcpy_s(editor_path, path.c_str());
    load(path);
    name = std::format("Sprite: {}", texture);
}

void Sprite::load(const std::string &path) {
    glDeleteTextures(1, &texture);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if ( path.empty() ) {
        loadColor();
    } else {
        // load and generate the texture
        stbi_set_flip_vertically_on_load(false);
        int width, height, nrChannels;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            GLenum format;
            if (nrChannels == 1) //nifty
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            spdlog::error("Failed to load sprite \"" + path + "\". Generating color pixel texture.");
            loadColor();
        }
        if (size == glm::vec2{0,0}) {
            size = { width, height };
            pos -= (size / 2.0f);
        }

        stbi_image_free(data);
    }
}

void Sprite::showImGuiDetails(Camera *camera) {
    ImGui::InputText("Path", editor_path, editor_path_len);
    ImGui::SameLine();
    if (ImGui::Button("Load")) {
        load(editor_path);
    }
    ImGui::DragFloat2("Pos", glm::value_ptr(pos));
    ImGui::DragFloat2("Size", glm::value_ptr(size));
    ImGui::ColorEdit3("Color", glm::value_ptr(color));
    static int e_tex;
    e_tex = static_cast<int>(texture);
    ImGui::InputInt("Texture ID", &e_tex);
    texture = static_cast<GLuint>(e_tex);
    static unsigned gid;
    gid = groupID;
    ImGui::InputInt("Group ID", reinterpret_cast<int *>(&groupID));
    if (gid != groupID) {
        *ztgk::game::scene->systemManager.getSystem<SignalQueue>() += HUDRemapGroupsSignalData::signal(
            false, uniqueID, type, gid, groupID, "Editor event."
        );
        gid = groupID;
    }
}

void Sprite::loadColor() {
    GLubyte clr[4] = { static_cast<GLubyte>(color.x * 255), static_cast<GLubyte>(color.y * 255), static_cast<GLubyte>(color.z * 255), static_cast<GLubyte>(color.w * 255) };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, clr);
    glGenerateMipmap(GL_TEXTURE_2D);
}
