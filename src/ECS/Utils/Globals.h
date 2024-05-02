//
// Created by cheily on 08.04.2024.
//

#pragma once

#include <memory>
#include "ECS/Scene.h"
#include "ECS/Render/ModelLoading/Model.h"

struct Cursor;
class SignalQueue;
struct GLFWwindow;

namespace ztgk::game {

    extern GLFWwindow * window;
    extern Scene * scene;
    extern Model * cube_model;
    extern Camera * camera;
    extern SignalQueue * signalQueue;

    extern Cursor cursor;

    extern std::atomic<bool> pause;
    extern std::atomic<bool> pause_render;

    extern glm::ivec2 window_size;
    extern bool fullscreen;

}