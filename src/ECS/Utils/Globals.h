//
// Created by cheily on 08.04.2024.
//

#pragma once

#include <memory>
#include "ECS/Scene.h"
#include "ECS/Render/ModelLoading/Model.h"

namespace ztgk::game {

    extern Scene * scene;
    extern Model * cube_model;

    extern std::atomic<bool> pause;
    extern std::atomic<bool> pause_render;

    extern glm::ivec2 window_size;
    extern bool fullscreen;

}