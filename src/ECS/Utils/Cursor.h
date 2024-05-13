//
// Created by cheily on 21.04.2024.
//

#pragma once


#include "glm/glm.hpp"
#include "imgui.h"
#include "ECS/SignalQueue/SignalReceiver.h"
#include "Globals.h"

enum dragSelectionMode{
    DRAG_UNIT,
    DRAG_TILE
};



struct Cursor {
    void init();
    void move(glm::vec2 newpos);
    void scroll(glm::vec2 offset);
    void click(int button, int action, int mods);

    struct cursor_conf {
        // capturing mouse will use it for ui navigation, otherwise it will be used for camera handling
        glm::bvec3 capture{true, true, true};
        bool & capture_move = capture.x;
        bool & capture_scroll = capture.y;
        bool & capture_click = capture.z;

        glm::bvec3 forward{true, true, true};
        bool & forward_move = forward.x;
        bool & forward_scroll = forward.y;
        bool & forward_click = forward.z;
    };
    cursor_conf config;

    glm::vec2 glfw_prev_pos {0};
    glm::vec2 ui_pos = ztgk::game::window_size / 2;
    glm::vec2 ui_prev_pos = ztgk::game::window_size / 2;
    ImGuiIO * mouseio;
    SignalReceiver toggleHandler;
    dragSelectionMode dragMode = DRAG_TILE;
};
