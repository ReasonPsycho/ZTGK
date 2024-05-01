//
// Created by cheily on 21.04.2024.
//

#pragma once


#include "glm/glm.hpp"
#include "imgui.h"
#include "ECS/SignalQueue/SignalReceiver.h"
#include "Globals.h"

struct Cursor {
    void init();
    void move(glm::vec2 newpos);
    void scroll(glm::vec2 offset);
    void press(int button, int action, int mods);

    struct cursor_conf {
        glm::bvec3 capture{true, true, true};
        bool & capture_move = capture.x;
        bool & capture_scroll = capture.y;
        bool & capture_press = capture.z;

        glm::bvec3 forward{true, true, true};
        bool & forward_move = forward.x;
        bool & forward_scroll = forward.y;
        bool & forward_press = forward.z;
    };
    cursor_conf config;

    bool capture = true;
    bool captureButton = true;
    glm::vec2 pos = ztgk::game::window_size / 2;
    glm::vec2 prev_pos = ztgk::game::window_size / 2;
    ImGuiIO * mouseio;
    SignalReceiver toggleHandler;
};
