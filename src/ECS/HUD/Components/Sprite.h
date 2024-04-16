//
// Created by cheily on 04.04.2024.
//

#pragma once

#include <string>
//#include <gl/GL.h>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glad/glad.h"
#include "ECS/Component.h"
#include "AHUDComponent.h"
#include "ECS/Utils/Config.h"
#include "ECS/Utils/Util.h"
#include "stb_image.h"

struct Sprite : public AHUDComponent {
    explicit Sprite(const std::string & path);
    explicit Sprite(const glm::vec2 &pos = ztgk::config::window_size / 2,
           const glm::vec2 &size = { 0, 0 },
           const glm::vec4 &color = ztgk::color.WHITE,
           unsigned int hudGroupId = 0,
           const std::string & path = "");

    glm::vec2 pos;
    glm::vec2 size;
    GLuint texture;
    glm::vec4 color;

    void load(const std::string & path);

    // editor
    static const unsigned editor_path_len = 100;
    char editor_path[editor_path_len];
    void showImGuiDetails(Camera *camera) override;

private:
    void loadColor();
};
