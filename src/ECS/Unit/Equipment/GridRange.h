//
// Created by cheily on 04.05.2024.
//

#pragma once


#include <vector>
#include "glm/vec2.hpp"
#include "ECS/Utils/Globals.h"
#include "ECS/Grid/Grid.h"

class Unit;

struct GridRange {
    explicit GridRange(int add = 1, int remove = 0);
    unsigned uniqueID;

    int add;
    int remove;
    std::vector<glm::ivec2> offsets;

    GridRange merge(int add, int remove);

    std::vector<glm::ivec2> get_indices(
        glm::ivec2 center,
        glm::ivec2 bounds_max = {ztgk::game::scene->systemManager.getSystem<Grid>()->width, ztgk::game::scene->systemManager.getSystem<Grid>()->height},
        glm::ivec2 bounds_min = {0, 0}
    );
    std::vector<Tile *> get_tiles(glm::ivec2 center);

    bool is_in_range(glm::ivec2 center, glm::ivec2 target_indices);

    static std::function<std::vector<Unit *>(const GridRange & range, glm::ivec2 center)> f_find_units_in_range;
    static std::function<std::vector<Unit *>(const GridRange & range, glm::ivec2 center)> f_find_sponges_in_range;
    static std::function<std::vector<Unit *>(const GridRange & range, glm::ivec2 center)> f_find_dirts_in_range;
    static std::function<std::vector<Unit *>(const GridRange & range, glm::ivec2 center)> f_find_units_in_range_sorted;
    static std::function<std::vector<Unit *>(const GridRange & range, glm::ivec2 center)> f_find_sponges_in_range_sorted;
    static std::function<std::vector<Unit *>(const GridRange & range, glm::ivec2 center)> f_find_dirts_in_range_sorted;

    // Finds any type of unit within the effective range. Excludes self.
    std::vector<Unit *> find_any(glm::ivec2 center);
    // Finds units with `isAlly() == false` within the effective range. Excludes self.
    std::vector<Unit *> find_enemies(glm::ivec2 center, bool mySide);
    // Finds units with `isAlly() == true` within the effective range. Excludes self.
    std::vector<Unit *> find_allies(glm::ivec2 center);

    void imgui_preview() const;
};
