//
// Created by cheily on 21.04.2024.
//

#pragma once


#include "glm/vec2.hpp"
#include "imgui.h"
#include "ECS/SignalQueue/SignalReceiver.h"
#include "Globals.h"

struct Cursor {
    void init();
    void take_input();

    bool capture = true;
    bool captureButton = true;
    glm::vec2 pos = ztgk::game::window_size / 2;
    ImGuiIO * mouseio;
    SignalReceiver toggleHandler;
};
