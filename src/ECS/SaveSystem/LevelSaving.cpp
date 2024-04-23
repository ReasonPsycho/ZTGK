//
// Created by cheily on 22.04.2024.
//

#include "YamlConverters.h"
#include "LevelSaving.h"
#include <yaml-cpp/yaml.h>
#include "ECS/Utils/Globals.h"
#include "ECS/Unit/UnitSystem.h"

using namespace ztgk;

char ztgk::tile_state_to_token(TileState state, TileStateData data) {
    switch (state) {
        case FLOOR:
            return TOKEN_FLOOR;
        case WALL:
            return TOKEN_WALL;
        case CHEST:
            // todo item type id
            return TOKEN_TREASURE_CHEST;
        case ORE:
            return TOKEN_ORE;
        case CORE:
            return TOKEN_CORE;
        case UNIT: {
            return TOKEN_PLAYER;
            // todo assign unit id when walking over, etc
//            auto & units = game::scene->systemManager.getSystem<UnitSystem>()->unitComponents;
//            auto it = std::find_if(units.begin(), units.end(), [data](Unit * unit){ return unit->uniqueID == data.unitId; });
//            if ( it != units.end() ) {
//                if ((*it)->IsAlly()) return TOKEN_PLAYER;
//                else return TOKEN_ENEMY_BASIC;  // todo enemy types/items
//            }
//            return TOKEN_ERROR;
        }
        case state_count:
            return TOKEN_ERROR;
    }
}

void ztgk::tile_init_from_token(char token, Tile * tile) {
    switch (token) {
        default:
        case TOKEN_ERROR:
            spdlog::error(std::format("Couldn't initialize tile x{} z{} from token '{}'", tile->index.x, tile->index.z, token));
            tile->state = FLOOR;
            break;
        case TOKEN_FLOOR:
            tile->state = FLOOR;
            break;
        case TOKEN_WALL:
            tile->state = WALL;
            break;
        case TOKEN_TREASURE_CHEST:
            tile->state = CHEST;
            // todo itemId
            break;
        case TOKEN_CORE:
            tile->state = CORE;
            break;
        case TOKEN_ORE:
            tile->state = ORE;
            break;
        case TOKEN_ENEMY_BASIC: // todo enemy types
        case TOKEN_PLAYER:
            tile->state = UNIT;
            // todo unitId
            break;
    }
    
    // todo remove this with vacant
    tile->vacant = tile->state == FLOOR;
}

void LevelSaving::save(const std::string& path) {
    auto thr = std::thread([path](){
        auto grid = ztgk::game::scene->systemManager.getSystem<Grid>();

        spdlog::trace(std::format("Saving to {}", path));
        YAML::Node node;
        std::vector<std::string> layout(grid->height, "");

        spdlog::trace("Serializing grid");
        char token;
        for (int z = 0; z < grid->height; ++z) {

            for (int x = 0; x < grid->width; ++x) {
                auto tile = grid->getTileAt(x, z);

                if ( tile == nullptr ) token = TOKEN_ERROR;
                else token = ztgk::tile_state_to_token(tile->state);

//                else if ( tile->state == FLOOR ) token = TOKEN_FLOOR;
//                else token = TOKEN_WALL;

                layout[z] += token;
            }
        }

        node["grid"]["width"] = grid->width;
        node["grid"]["height"] = grid->height;
        spdlog::trace("Serializing units");
        auto units = ztgk::game::scene->systemManager.getSystem<UnitSystem>()->unitComponents;

//        node["units"].SetStyle(YAML::EmitterStyle::Flow);
        for (auto & unit : units) {
            if (unit->IsAlly())
                layout[unit->gridPosition.z][unit->gridPosition.x] = TOKEN_PLAYER;
            else layout[unit->gridPosition.z][unit->gridPosition.x] = TOKEN_ENEMY_BASIC;
//            unit->equipment.item1->name
        }

        std::ofstream out = std::ofstream(path);
        spdlog::trace("Writing layout");
        out << TOKEN_LAYOUT_START << '\n';
        for ( auto & row : layout ) {
            out << TOKEN_LAYOUT_LINE << row << '\n';
        }
        out << TOKEN_LAYOUT_END << '\n';
        spdlog::trace("Writing node");
        out << node;
        spdlog::trace("Save complete");
    });
    thr.detach();
}

void LevelSaving::load(const std::string& path) {
    auto thr = std::thread([path](){
        spdlog::trace(std::format("Loading level from {}", path));
        auto grid = ztgk::game::scene->systemManager.getSystem<Grid>();

        spdlog::trace("Reading layout");
        int x = 0, z = 0;
        auto in = std::ifstream(path);
        std::string line;
        bool read = false;
        while ( std::getline(in, line) && line != TOKEN_LAYOUT_END ) {
            if ( line == TOKEN_LAYOUT_START ) {
                read = true;
                continue;
            }
            if ( !read ) continue;

            line = line.substr(line.find_first_not_of(TOKEN_LAYOUT_LINE));
            for (char token : line) {
                auto tile = grid->getTileAt(x, z);

                tile_init_from_token(token, tile);
//                if ( token == TOKEN_FLOOR ) {
//                    tile->vacant = true;
//                }
//                else if ( token == TOKEN_WALL ) {
//                    tile->vacant = false;
//                }
                ++x;
                if ( x == grid->width ) x = 0;
            }

            ++z;
        }

        spdlog::trace("Reading node");
        // todo

//        spdlog::trace("Generating entities");
//        grid->LoadTileEntities(1.0f, ztgk::game::scene->systemManager.getSystem<CollisionSystem>());
        spdlog::trace("Finished loading");

    });
    thr.detach();
}
