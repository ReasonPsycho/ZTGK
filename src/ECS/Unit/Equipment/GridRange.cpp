//
// Created by cheily on 04.05.2024.
//

#include "GridRange.h"
#include "ECS/Utils/Globals.h"
#include "ECS/Unit/Unit.h"
#include "ECS/Grid/Tile.h"
#include "ECS/Utils/Util.h"
#include <ranges>

using namespace ztgk;

//|4|3|2|3|4|
//|3|2|1|2|3|
//|2|1|1|1|2|
//|3|2|1|2|3|
//|4|3|2|3|4|
GridRange::GridRange(int add, int remove) : uniqueID(id<ID_POOL_GRID_RANGE>()), add(add), remove(remove) {
    offsets = {};

    for(int z = -add; z <= add; ++z) {
        for (int x = -add; x <= add; ++x) {
            // this is just the circle formula without power gives rhombus
            // https://www.desmos.com/calculator/46kpd5a2bf
            auto dist = abs(x) + abs(z);
            if (z == 0 && x == 0 && remove == 0) {
                offsets.emplace_back(x, z);
            } else if (dist <= add && dist > remove)
                offsets.emplace_back(x, z);
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
        return tile->unit != nullptr && tile->unit->isAlive;
    });
    std::vector<Unit *> ret{};
    for (auto & tile : tiles) {
        ret.push_back(tile->unit);
    }
    return ret;
}
                                                                    //vv mySide defines if the unit that looks for its enemies is on player side or bug side
std::vector<Unit *> GridRange::find_my_enemies(glm::ivec2 center, bool mySide) {
    auto tiles = get_tiles(center) | std::ranges::views::filter([&mySide](Tile * tile){
        return tile->unit != nullptr && tile->unit->isAlive && tile->unit->IsAlly() != mySide;
    });
    std::vector<Unit *> ret{};
    for (auto & tile : tiles) {
        ret.push_back(tile->unit);
    }
    return ret;
}

std::vector<Unit *> GridRange::find_my_allies(glm::ivec2 center, bool mySide) {
    auto tiles = get_tiles(center) | std::ranges::views::filter([mySide](Tile * tile){
        return tile->unit != nullptr && tile->unit->isAlive && tile->unit->IsAlly() == mySide;
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
    if (ImGui::TreeNode(std::format("Range: {}-{}##range_{}", add, remove, uniqueID).c_str())) {
        for (auto & offset : offsets) {
            ImGui::Text("x,z : [%d,%d]", offset.x, offset.y);
        }
        ImGui::TreePop();
    }
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
