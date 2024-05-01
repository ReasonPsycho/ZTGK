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

void Cursor::init() {
    mouseio = &ImGui::GetIO();
    toggleHandler = SignalReceiver{
        Signal::signal_types.keyboard,
        [this](const Signal& signal) {
            auto data = std::dynamic_pointer_cast<KeySignalData>(signal.data);
            if (data->key == GLFW_KEY_GRAVE_ACCENT && data->action == GLFW_PRESS) {
                config.capture_move = !config.capture_move;
                config.capture_press = !config.capture_press;
                config.capture_scroll = !config.capture_scroll;
            }
        }
    };
}

void Cursor::move(glm::vec2 newpos) {
    if (!config.capture_move) return;
}

void Cursor::scroll(glm::vec2 offset) {
    if (!config.capture_scroll) return;
    ztgk::game::camera->ProcessMouseScroll(static_cast<float>(offset.y), Time::Instance().DeltaTime());
    if (config.forward_scroll) *ztgk::game::signalQueue += MouseScrollSignalData::signal(offset, "Cursor forwarding GLFW event.");
}

void Cursor::press(int button, int action, int mods) {
    if (!config.capture_press) return;
}
