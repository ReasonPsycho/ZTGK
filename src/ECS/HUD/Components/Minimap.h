//
// Created by cheily on 13.06.2024.
//

#pragma once

#include "AHUDComponent.h"

struct Minimap : public AHUDComponent {
    glm::vec4 colors[100][100];
    glm::vec2 size;

    explicit Minimap(const glm::vec2 &pos = { 0, 0 },
                     const glm::vec2 &size = { 400, 400 },
                     unsigned int hudGroupId = 0);

    void UpdateImpl() override;
};
