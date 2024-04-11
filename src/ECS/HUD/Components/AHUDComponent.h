//
// Created by cheily on 09.04.2024.
//

#pragma once

#include "ECS/Component.h"

struct AHUDComponent : public Component {
    enum hudcType {
        UNDEFINED,
        SPRITE, TEXT
    };

    AHUDComponent(hudcType type, unsigned int groupId) : type(type), groupID(groupId) {}
    virtual ~AHUDComponent() = default;

    hudcType type;
    unsigned groupID;
};
