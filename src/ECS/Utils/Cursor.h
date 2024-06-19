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
    void update();
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
    glm::vec2 raw_pos = ztgk::game::window_size / 2;
    glm::vec2 raw_prev_pos = ztgk::game::window_size / 2;
    glm::vec2 ui_pos = ztgk::game::window_size / 2;
    glm::vec2 ui_prev_pos = ztgk::game::window_size / 2;
#ifdef DEBUG_BUILD
    ImGuiIO * mouseio;
#endif
    SignalReceiver toggleHandler;

    inline void update_ui_pos() {
        //todo once cursor icons are real, verify if the position is correctly aligned with the icon's pivot (it seems there's a slight offset?)
        ui_pos = {raw_pos.x, ztgk::game::window_size.y - raw_pos.y};
        ui_prev_pos = {raw_prev_pos.x, ztgk::game::window_size.y - raw_prev_pos.y};
    }
};
