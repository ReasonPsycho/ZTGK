//
// Created by cheily on 04.05.2024.
//

#include "GridRange.h"
#include "ECS/Utils/Globals.h"
#include "ECS/Unit/Unit.h"
#include "ECS/Grid/Tile.h"
#include <ranges>

//|4|3|2|3|4|
//|3|2|1|2|3|
//|2|1|1|1|2|
//|3|2|1|2|3|
//|4|3|2|3|4|
GridRange::GridRange(int add, int remove) : add(add), remove(remove) {
    offsets = {};

    // center line
    for (int x = -add; x <= add; ++x) {
        if ( remove == 0 || (x < -remove || x > remove) )
            offsets.emplace_back(x, 0);
    }

    for (int z = 1; z <= add; ++z) {
        for (int x = -add + z; x <= add - z; ++x) {
            // todo this is not correct
            if (remove == 0 || ((x < -remove || x > remove) && (z < -remove || z > remove)) ) {
                offsets.emplace_back(x, z);
                offsets.emplace_back(x, -z);
            }
        }
    }
}

std::vector<glm::ivec2> GridRange::get_indices(glm::ivec2 center, glm::ivec2 bounds_max, glm::ivec2 bounds_min) {
    std::vector<glm::ivec2> ret{};
    for (auto & offset : offsets) {
        auto pos = center + offset;
        if ( pos.x < bounds_min.x || pos.y < bounds_min.y || pos.x >= bounds_max.x || pos.y >= bounds_max.y )
            continue;
        ret.emplace_back(pos);
    }
    return ret;
}

std::vector<Tile *> GridRange::get_tiles(glm::ivec2 center) {
    std::vector<Tile *> ret{};
    auto grid = ztgk::game::scene->systemManager.getSystem<Grid>();

    glm::ivec2 bounds = { grid->width, grid->height };
    for (auto & offset : offsets) {
        glm::ivec2 pos = center + offset;
        if ( pos.x < 0 || pos.y < 0 || pos.x >= bounds.x || pos.y >= bounds.y )
            continue;
        ret.push_back(grid->getTileAt(pos.x, pos.y));
    }
    return ret;
}

std::vector<Unit *> GridRange::find_any(glm::ivec2 center) {
    auto tiles = get_tiles(center) | std::ranges::views::filter([](Tile * tile){
        return tile->unit != nullptr;
    });
    std::vector<Unit *> ret{};
    for (auto & tile : tiles) {
        ret.push_back(tile->unit);
    }
    return ret;
}

std::vector<Unit *> GridRange::find_enemies(glm::ivec2 center) {
    auto tiles = get_tiles(center) | std::ranges::views::filter([](Tile * tile){
        return tile->unit != nullptr && !tile->unit->IsAlly();
    });
    std::vector<Unit *> ret{};
    for (auto & tile : tiles) {
        ret.push_back(tile->unit);
    }
    return ret;
}

std::vector<Unit *> GridRange::find_allies(glm::ivec2 center) {
    auto tiles = get_tiles(center) | std::ranges::views::filter([](Tile * tile){
        return tile->unit != nullptr && tile->unit->IsAlly();
    });
    std::vector<Unit *> ret{};
    for (auto & tile : tiles) {
        ret.push_back(tile->unit);
    }
    return ret;
}

GridRange GridRange::merge(int add, int remove) {
    return GridRange(this->add + add, this->remove + remove);
}

bool GridRange::is_in_range(glm::ivec2 center, glm::ivec2 target_indices) {
    auto ind = get_indices(center);
    return std::find(ind.begin(), ind.end(), target_indices) != ind.end();
}

void GridRange::imgui_preview() const {
    ImGui::Text("%s", std::format("Range: {}-{}", add, remove).c_str());
    if (ImGui::IsItemHovered()) {
        std::string visual;
        for(int z = -add; z <= add; ++z) {
            for (int x = -add; x <= add; ++x) {
                // this is just the circle formula simplified for rhombus
                // https://www.desmos.com/calculator/46kpd5a2bf
                auto dist = abs(x) + abs(z);
                if (z == 0 && x == 0)
                    visual += 'x';
                else if (dist <= add && dist > remove)
                    visual += '+';
                else if (dist <= remove)
                    visual += '-';
                else visual += ' ';
            }
            visual += '\n';
        }
        ImGui::SetTooltip("%s", visual.c_str());
    }
}
