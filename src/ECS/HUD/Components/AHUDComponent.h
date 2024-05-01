//
// Created by cheily on 09.04.2024.
//

#pragma once

#include "ECS/Component.h"

enum hudcType {
    UNDEFINED,
    SPRITE, TEXT
};

struct AHUDComponent : public Component {
    AHUDComponent(hudcType type, unsigned int groupId) : type(type), groupID(groupId) {}
    virtual ~AHUDComponent() = default;

    hudcType type;
    unsigned groupID;
    glm::vec2 pos;
};
