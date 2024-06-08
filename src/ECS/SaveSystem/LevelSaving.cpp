//
// Created by cheily on 22.04.2024.
//

#include "YamlConverters.h"
#include "LevelSaving.h"
#include <yaml-cpp/yaml.h>
#include "ECS/Utils/Globals.h"
#include "ECS/Unit/UnitSystem.h"
#include "ECS/Gameplay/WashingMachine.h"

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
        case SPONGE: {
            return TOKEN_PLAYER;
            // todo assign unit id when walking over, etc
//            auto & units = game::scene->systemManager.getSystem<UnitSystem>()->unitComponents;
//            auto it = std::find_if(units.begin(), units.end(), [data](Unit * unit){ return unit->uniqueID == data.unitId; });
//            if ( it != units.end() ) {
//                if ((*it)->IsAlly()) return TOKEN_PLAYER;
//                else return TOKEN_ENEMY_BUG;  // todo enemy types/items
//            }
//            return TOKEN_ERROR;
        }
        case state_count:
            return TOKEN_ERROR;
    }
}

void ztgk::tile_state_from_token(char token, Tile * tile) {
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
            // todo itemTypeId, once relevant
            break;
        case TOKEN_CORE:
            tile->state = CORE;
            break;
        case TOKEN_ORE:
            tile->state = ORE;
            break;
        case TOKEN_ENEMY_BUG:
            tile->state = BUG;
            break;
        case TOKEN_PLAYER:
            // tile doesn't hold any unit reference anymore (ID serialization is unreliable, some other type of manually assigned ID would be necessary)
            //  todo if there are other tokens for unit types, add them here, tile is unaware of any specifics about the unit standing on it
            tile->state = SPONGE;
            break;
    }
}

void LevelSaving::save(const std::string& path) {
//    auto thr = std::thread([path](){
        auto grid = ztgk::game::scene->systemManager.getSystem<Grid>();

        spdlog::info(std::format("Saving to {}", path));
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

        for (auto & unit : units) {
            if (unit->IsAlly()) {
                layout[unit->gridPosition.z][unit->gridPosition.x] = TOKEN_PLAYER;
                node["allies"].push_back(*unit);
            }
            else {
                layout[unit->gridPosition.z][unit->gridPosition.x] = TOKEN_ENEMY_BUG;
                node["enemies"].push_back(*unit);
            }
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
        spdlog::info("Save complete");
//    });
//    thr.detach();
}

void LevelSaving::load(const std::string& path) {
//    auto thr = std::thread([path](){
//        ztgk::game::pause_render = true;
        spdlog::info(std::format("Loading level from {}", path));
        auto grid = ztgk::game::scene->systemManager.getSystem<Grid>();

        auto node = YAML::LoadFile(path);
        spdlog::trace("Clearing grid");
        grid->ClearWalls();
        grid->ClearAllWallData();
        spdlog::trace("Re-generating grid entities");
        grid->reinitWithSize({node["grid"]["width"].as<int>(), node["grid"]["height"].as<int>()});

        spdlog::trace("Reading grid layout to tile state");
        int z = 0;
        auto in = std::ifstream(path);
        std::string line;
        bool read = false;
        while ( std::getline(in, line) && line != TOKEN_LAYOUT_END && z < grid->height ) {
            if ( line == TOKEN_LAYOUT_START ) {
                read = true;
                continue;
            }
            if ( !read ) continue;

            line = line.substr(line.find_first_not_of(TOKEN_LAYOUT_LINE));
            int x = 0;
            for (char token : line) {
                if ( x >= grid->width ) break;
                auto tile = grid->getTileAt(x, z);

                tile_state_from_token(token, tile);
                ++x;
            }

            ++z;
        }

        spdlog::trace("Initializing tiles with loaded state");
        grid->InitializeTileEntities();
        grid->SetUpWalls();
    grid->UpdateFogData(grid->centerTile);

        spdlog::trace("Reading node");
        auto units = ztgk::game::scene->systemManager.getSystem<UnitSystem>()->unitComponents;
        if (!units.empty()) {
            spdlog::warn("Units already existing! Aborting!");
        } else {
            spdlog::trace("Loading unit entities");
            for (auto unode: node["allies"]) {
                auto name = unode[nameof(quote(Entity::name))].as<std::string>();

                auto entity = Unit::serializer_newUnitEntity(ztgk::game::scene, name);
                YAML::convert<Unit>::decode(unode, *entity->getComponent<Unit>());
            }
        }
        ztgk::game::scene->systemManager.getSystem<WashingMachine>()->createWashingMachine(ztgk::game::washingMachineModel);
        // todo chests and stuff, once relevant

        spdlog::info("Finished loading");
//        ztgk::game::pause_render = false;
//    });
//    thr.detach();
}
