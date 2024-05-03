//
// Created by cheily on 11.04.2024.
//

#include "Globals.h"
#include "Cursor.h"
#include "ECS/SignalQueue/SignalQueue.h"
#include "GLFW/glfw3.h"

namespace ztgk::game {
    // defaults
    GLFWwindow * game::window = nullptr;
    Scene * game::scene = nullptr;
    Model * game::cube_model = nullptr;
    Camera * game::camera = nullptr;
    SignalQueue * game::signalQueue = nullptr;
    Cursor game::cursor = {};
    std::atomic<bool> game::pause = false;
    std::atomic<bool> game::pause_render = false;
    glm::ivec2 game::window_size = { 1920, 1080 };
    bool game::fullscreen = false;

}