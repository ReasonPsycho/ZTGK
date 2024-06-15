//
// Created by cheily on 13.06.2024.
//

#include "Minimap.h"
#include "ECS/Grid/Tile.h"
#include "ECS/Utils/Util.h"
#include "ECS/Utils/Globals.h"
#include "ECS/Grid/Grid.h"

Minimap::Minimap(const glm::vec2 &pos, const glm::vec2 &size, unsigned int hudGroupId)
    : AHUDComponent(hudcType::MINIMAP, hudGroupId), size(size) {
        this->pos = pos;
        this->name = "Minimap";
        for (int y = 0; y < 100; ++y) {
            for (int x = 0; x < 100; ++x) {
                colors[y][x] = ztgk::color.GRAY;
            }
        }
}

void Minimap::UpdateImpl() {
    auto get_color = [](Tile * tile) -> glm::vec4 {
        if (tile->isInFogOfWar)
            return ztgk::color.WHITE;
        switch (tile->state) {
            default:
            case FLOOR:
                return ztgk::color.GRAY;
            case WALL:
                return ztgk::color.BLACK;
            case SPONGE:
                return ztgk::color.YELLOW;
            case BUG: case SHROOM:
                return ztgk::color.RED;
            case CHEST:
                return ztgk::color.ORANGE;
            case ORE:
                return ztgk::color.CYAN;
            case CORE:
                return ztgk::color.BLUE;
        }
    };

    for (int y = 0; y < 100; ++y) {
        for (int x = 0; x < 100; ++x) {
            Tile *tile = ztgk::game::scene->systemManager.getSystem<Grid>()->getTileAt(x, y);
            colors[x][y] = get_color(tile);
        }
    }
}
