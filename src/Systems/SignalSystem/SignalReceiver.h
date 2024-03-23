//
// Created by cheily on 20.03.2024.
//

#pragma once

#include "ECS/Component.h"
#include <functional>
#include <string>
struct Signal;
class Camera;

struct SignalReceiver : Component {
    static std::unordered_map<unsigned, std::pair<SignalReceiver*, std::vector<std::string>>> debugClones;

    unsigned uid;

    unsigned receive_type_mask = 0;
    std::function<void(const Signal&)> receive{};

    SignalReceiver();
    SignalReceiver(unsigned int receiveTypeMask, std::function<void(const Signal &)> onSignal);
    virtual ~SignalReceiver() = default;

    void showImGuiDetails(Camera *camera) override;
};


