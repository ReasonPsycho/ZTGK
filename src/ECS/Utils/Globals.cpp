//
// Created by cheily on 11.04.2024.
//

#include "Globals.h"

namespace ztgk::game {

    Scene * game::scene = nullptr;
    bool game::pause = false;
    glm::ivec2 game::window_size = { 1920, 1080 };
    bool game::fullscreen = false;

}