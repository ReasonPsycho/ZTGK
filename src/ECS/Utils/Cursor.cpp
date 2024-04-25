//
// Created by cheily on 21.04.2024.
//

#include "Cursor.h"
#include "ECS/SignalQueue/Signal.h"
#include "ECS/SignalQueue/DataCargo/KeySignalData.h"
#include "GLFW/glfw3.h"

void Cursor::init() {
    mouseio = &ImGui::GetIO();
    toggleHandler = SignalReceiver{
        Signal::signal_types.keyboard,
        [this](const Signal& signal) {
            auto data = std::dynamic_pointer_cast<KeySignalData>(signal.data);
            if (data->key == GLFW_KEY_GRAVE_ACCENT && data->action == GLFW_PRESS) {
                capture = true;
                captureButton = true;
            }
        }
    };
}
