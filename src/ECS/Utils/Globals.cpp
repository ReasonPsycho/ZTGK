//
// Created by cheily on 11.04.2024.
//

#include "Globals.h"

namespace ztgk::game {

    Scene * game::scene = nullptr;
    Model * game::cube_model = nullptr;
    std::atomic<bool> game::pause = false;
    std::atomic<bool> game::pause_render = false;
    glm::ivec2 game::window_size = { 1920, 1080 };
    bool game::fullscreen = false;

}