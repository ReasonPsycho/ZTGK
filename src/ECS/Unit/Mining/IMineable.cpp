//
// Created by igork on 24.03.2024.
//

#include "IMineable.h"

#include "ECS/SignalQueue/SignalReceiver.h"
#include "ECS/Utils/Time.h"
#include "ECS/HUD/Components/Text.h"

IMineable::IMineable(float timeToMine) {
    this->name = "IMineable";
    this->timeToMine = timeToMine;
    this->timeToMineRemaining = timeToMine;
}

void IMineable::Mine() {
    timeToMineRemaining -= Time::Instance().DeltaTime();
    if (timeToMineRemaining<=0) {
        delete this;
    }
}

void IMineable::Update() {

}

void IMineable::showImGuiDetails(Camera *camera) {
    ImGui::Text("Time to mine: %f", timeToMine);
    ImGui::Text("Time to mine remaining: %f", timeToMineRemaining);

}
