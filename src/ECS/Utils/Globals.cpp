//
// Created by cheily on 11.04.2024.
//

#include "Globals.h"
#include "Cursor.h"
#include "ECS/SignalQueue/SignalQueue.h"
#include "GLFW/glfw3.h"

namespace ztgk::game {
    // defaults
    s_ui_data game::ui_data = {};
    GLFWwindow * game::window = nullptr;
    Scene * game::scene = nullptr;
    Model * game::cube_model = nullptr;
    Camera * game::camera = nullptr;
    SignalQueue * game::signalQueue = nullptr;
    Cursor game::cursor = {};
    int game::pranium_needed_to_win = 10;
    std::atomic<bool> game::pause = false;
    std::atomic<bool> game::pause_render = false;
    glm::ivec2 game::window_size = { 1920, 1080 };
    bool game::fullscreen = false;
    float game::saturationMultiplayer = 1.5;
    float game::lightMultiplayer = 1.2;
    int game::toon_color_levels = 15;
    Model * game::washingMachineModel = nullptr;
    Model * game::praniumModel = nullptr;
    AudioManager * game::audioManager = nullptr;
    SignalReceiver * game::selectionHandler = nullptr;
    Model * game::playerModel = nullptr;
    Model * game::bugModel = nullptr;
    Model * game::shroomModel = nullptr;
    Model * game::oreModel = nullptr;
    Model * game::chestModel = nullptr;
    Model * game::projectileModel = nullptr;
    Model * game::mopModel = nullptr;
    Model * game::mopObrotowyModel = nullptr;
    Model * game::tidyPodLauncherModel = nullptr;

    bool game::gameStarted = false;
    bool game::gameWon = false;
    bool game::gameLost = false;
}