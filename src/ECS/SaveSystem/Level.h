//
// Created by cheily on 23.04.2024.
//

#pragma once

#include "ECS/Grid/Grid.h"
#include "ECS/Unit/Unit.h"

struct Level {
    Grid * grid;
    std::vector<glm::ivec3> units;

};
