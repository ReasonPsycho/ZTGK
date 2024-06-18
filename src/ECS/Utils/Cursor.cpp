//
// Created by cheily on 21.04.2024.
//

#include "Cursor.h"
#include "ECS/SignalQueue/Signal.h"
#include "ECS/SignalQueue/DataCargo/KeySignalData.h"
#include "GLFW/glfw3.h"
#include "Time.h"
#include "ECS/SignalQueue/SignalQueue.h"
#include "ECS/SignalQueue/DataCargo/MouseEvents/MouseScrollSignalData.h"
#include "ECS/SignalQueue/DataCargo/MouseEvents/MouseMoveSignalData.h"
#include "imgui_impl_glfw.h"
#include "ECS/SignalQueue/DataCargo/MouseEvents/MouseButtonSignalData.h"

void Cursor::init() {
#ifdef DEBUG_BUILD
    mouseio = &ImGui::GetIO();
#endif
    double tx, ty;
    glfwGetCursorPos(ztgk::game::window, &tx, &ty);
    glfw_prev_pos = {tx, ty};
    raw_pos = glfw_prev_pos;
    raw_prev_pos = glfw_prev_pos;
    update_ui_pos();
    toggleHandler = SignalReceiver{
        Signal::signal_types.keyboard,
        [this](const Signal& signal) {
            auto data = std::dynamic_pointer_cast<KeySignalData>(signal.data);
            if (data->key == GLFW_KEY_GRAVE_ACCENT && data->action == GLFW_PRESS) {
                config.capture_move = !config.capture_move;
                config.capture_click = !config.capture_click;
                config.capture_scroll = !config.capture_scroll;
            }
            if (data->key == GLFW_KEY_R && data->mods == GLFW_MOD_CONTROL && data->action == GLFW_PRESS) {
                raw_pos = ztgk::game::window_size / 2;
                raw_prev_pos = ztgk::game::window_size / 2;
#ifdef RELEASE_BUILD
                glfwSetCursorPos(ztgk::game::window, raw_pos.x, raw_pos.y);
#endif
                update_ui_pos();
            }
        }
    };
    *ztgk::game::signalQueue += &toggleHandler;
}

void Cursor::move(glm::vec2 newpos) {
    auto glfw_offset = glfw_prev_pos - newpos;
    if (config.capture_move) {
        raw_prev_pos = raw_pos;
        raw_pos -= glfw_offset;
#ifdef DEBUG_BUILD
        mouseio->MousePos = {raw_pos.x, raw_pos.y};
#endif
        update_ui_pos();
        if (config.forward_move) {
            *ztgk::game::signalQueue += MouseMoveSignalData::signal(ui_pos,ui_prev_pos,"Cursor forwarding MOVE");
        }
    } else {
        ztgk::game::camera->ProcessMouseMovement(-glfw_offset.x, glfw_offset.y, true, Time::Instance().DeltaTime());
    }
    glfw_prev_pos = newpos;
}

void Cursor::scroll(glm::vec2 offset) {
    if (config.capture_scroll) {
#ifdef DEBUG_BUILD
        ImGui_ImplGlfw_ScrollCallback(ztgk::game::window, offset.x, offset.y);
#endif
        if (config.forward_scroll) {
            *ztgk::game::signalQueue += MouseScrollSignalData::signal(offset, raw_pos, "Cursor forwarding SCROLL");
        }
    } else {
        ztgk::game::camera->ProcessMouseScroll(static_cast<float>(offset.y), Time::Instance().DeltaTime());
    }
}

void Cursor::click(int button, int action, int mods) {
    if (config.capture_click) {
#ifdef DEBUG_BUILD
        ImGui_ImplGlfw_MouseButtonCallback(ztgk::game::window, button, action, mods);
#endif
        if (config.forward_click) {
            *ztgk::game::signalQueue += MouseButtonSignalData::signal(button, action, mods,
                                          {raw_pos.x, ztgk::game::window_size.y - raw_pos.y},
                                          "Cursor forwarding CLICK");

        }
    }
}

void Cursor::update() {
    ztgk::game::camera->MoveCamera(raw_pos.x,raw_pos.y);
}
