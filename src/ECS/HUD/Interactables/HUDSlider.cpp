//
// Created by cheily on 21.05.2024.
//

#include "HUDSlider.h"
#include "ECS/HUD/Components/Text.h"
#include "ECS/HUD/Components/Sprite.h"
#include "ECS/HUD/Interactables/HUDButton.h"
#include "ECS/HUD/HUD.h"
#include "ECS/SignalQueue/Signal.h"
#include "ECS/SignalQueue/SignalQueue.h"
#include "ECS/SignalQueue/DataCargo/MouseEvents/MouseMoveSignalData.h"
#include "ECS/Entity.h"

HUDSlider::HUDSlider(
        SliderDirection direction, Sprite *displayBar, Sprite *barBackground, unsigned int groupID,
        HUDButton *control, HUDButton *controlHandle, Sprite *controlHandleForeground,
        Text *display, float displayMin, float displayMax
) : AHUDComponent(SLIDER, groupID), value(1), direction(direction), bar(displayBar), barBackground(barBackground),
   control(control), controlHandle(controlHandle), controlHandleForeground(controlHandleForeground),
   display(display), displayMin(displayMin), displayMax(displayMax) {
    if (controlHandle)
        name = "Setting Slider";
    else if (control)
        name = "Controllable Bar";
    else name = "Bar";

    if (display) {
        name += " + display";
    }
}

void HUDSlider::set(float value) {
    this->value = clamp(value, 0.0f, 1.0f);
    switch (direction) {
    case HORIZONTAL:
        bar->size.x = barBackground->size.x * this->value;
        break;
    case VERTICAL:
        bar->size.y = barBackground->size.y * this->value;
        break;
    }

    update_display();
}

void HUDSlider::set_in_display_range(float value) {
    set(clamp((value - displayMin) / (displayMax - displayMin), displayMin, displayMax));
}

void HUDSlider::set_direction(SliderDirection direction) {
    this->direction = direction;
    switch (direction) {
    case HORIZONTAL:
        bar->size.x = barBackground->size.x * value;
        bar->size.y = barBackground->size.y;
        break;
    case VERTICAL:
        bar->size.y = barBackground->size.y * value;
        bar->size.x = barBackground->size.x;
        break;
    }
}

float HUDSlider::get_in_display_range() const {
    return displayMin + value * (displayMax - displayMin);
}

std::string HUDSlider::get_display_string() const {
    return std::vformat(displayFormat, std::make_format_args(get_in_display_range(), displayMax));
}

void HUDSlider::showImGuiDetailsImpl(Camera *camera) {
    ImGui::SliderFloat(std::format("Value##{}", uniqueID).c_str(), &value, 0, 1);
    static float valueInDisplayRange = get_in_display_range();
    ImGui::SliderFloat(std::format("Value in display range##{}", uniqueID).c_str(), &valueInDisplayRange, displayMin, displayMax);
    ImGui::Combo(std::format("Direction##{}", uniqueID).c_str(), (int *) &direction, "Horizontal\0Vertical\0");
    if (ImGui::Button(std::format("Set##{}", uniqueID).c_str())) {
        set(value);
    }
    ImGui::SameLine();
    if (ImGui::Button(std::format("Set in display range##{}", uniqueID).c_str())) {
        set_in_display_range(valueInDisplayRange);
    }
    ImGui::SameLine();
    if (ImGui::Button(std::format("Set direction##{}", uniqueID).c_str())) {
        set_direction(direction);
    }
}

void HUDSlider::init_control_listener() {
    parentEntity->addComponent(std::make_unique<SignalReceiver>(
        Signal::signal_types.mouse_move_signal,
        [this](const Signal & signal) {
            if (!this->isListening)
                return;

            auto data = dynamic_pointer_cast<MouseMoveSignalData>(signal.data);
            switch (this->direction) {
            case HORIZONTAL:
                this->set_from_pos(data->pos);
                break;
            case VERTICAL:
                this->set_from_pos(data->pos);
                break;
            }
        }
    ));
    controlListener = parentEntity->getComponent<SignalReceiver>();
    *ztgk::game::signalQueue += controlListener;
}

void HUDSlider::set_from_pos(glm::vec2 pos) {
    auto hud = ztgk::game::scene->systemManager.getSystem<HUD>();

    switch (this->direction) {
    case HORIZONTAL:
        this->set(std::clamp((pos.x - this->control->collisionSprite->pos.x - hud->getGroupTreeOffset(control->groupID).x) / this->control->collisionSprite->size.x, 0.0f, 1.0f));
        break;
    case VERTICAL:
        this->set(std::clamp((pos.y - this->control->collisionSprite->pos.y - hud->getGroupTreeOffset(control->groupID).y) / this->control->collisionSprite->size.y, 0.0f, 1.0f));
        break;
    }
}

void HUDSlider::update_display() {
    if (controlHandle && controlHandleForeground) {
        switch (direction) {
        case HORIZONTAL:
            controlHandle->collisionSprite->pos.x = barBackground->pos.x + barBackground->size.x * value;
            controlHandleForeground->pos.x = controlHandle->collisionSprite->pos.x;
            break;
        case VERTICAL:
            controlHandle->collisionSprite->pos.y = barBackground->pos.y + barBackground->size.y * value;
            controlHandleForeground->pos.y = controlHandle->collisionSprite->pos.y;
            break;
        }
    }
    if (display) {
        display->content = get_display_string();
        if (controlHandle) {
            switch (direction) {
            case HORIZONTAL:
                display->pos.x = controlHandle->collisionSprite->pos.x;
                break;
            case VERTICAL:
                display->pos.y = controlHandle->collisionSprite->pos.y;
                break;
            }
        }
    }
}
