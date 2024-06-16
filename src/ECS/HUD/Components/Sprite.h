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
#include "ECS/Utils/Globals.h"
#include "ECS/Utils/Util.h"
#include "stb_image.h"  // do not remove this!!

struct Sprite : public AHUDComponent {
    explicit Sprite(const std::string & path);
    explicit Sprite(const glm::vec2 &pos = ztgk::game::window_size / 2,
           const glm::vec2 &size = { 0, 0 },
           const glm::vec4 &color = ztgk::color.WHITE,
           unsigned int hudGroupId = 0,
           const std::string & path = "");

    std::string loaded_path = "";
    glm::vec2 size;
    GLuint texture = -1;
    glm::vec4 color;
    bool hasTexture = false;

    void load(const std::string & path = "", bool force = false);

    // editor
    static const unsigned editor_path_len = 100;
    char editor_path[editor_path_len];
    void showImGuiDetailsImpl(Camera *camera) override;
};
