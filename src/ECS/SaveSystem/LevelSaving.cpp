//
// Created by cheily on 22.04.2024.
//

#include "YamlConverters.h"
#include "LevelSaving.h"
#include <yaml-cpp/yaml.h>
#include <filesystem>
#include "ECS/Utils/Globals.h"
#include "ECS/Unit/UnitSystem.h"
#include "ECS/Gameplay/WashingMachine.h"
#include "ECS/HUD/HUD.h"
#include "ECS/HUD/Components/Sprite.h"
#include "ECS/SignalQueue/Signal.h"
#include "ECS/SignalQueue/SignalQueue.h"
#include "ECS/SignalQueue/DataCargo/LevelSaveLoadSignals/LoadSignal.h"

using namespace ztgk;

char ztgk::tile_state_to_token(TileState state, TileStateData data) {
    switch (state) {
        case FLOOR:
            return TOKEN_FLOOR;
        case WALL:
            return TOKEN_WALL;
        case CHEST:
            // todo item type id
            return TOKEN_TREASURE_CHEST_0 + data.chestItemTypeId;
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
//                else return TOKEN_ENEMY_BUG;  // todo bug types/items
//            }
//            return TOKEN_ERROR;
        }
        case BUG:
            return TOKEN_ENEMY_BUG;
        case SHROOM:
            return TOKEN_ENEMY_SHROOM;
        case state_count:
            return TOKEN_ERROR;
    }
}

void ztgk::tile_state_from_token(char token, Tile * tile) {
    if (token >= TOKEN_TREASURE_CHEST_0 && token <= TOKEN_TREASURE_CHEST_9) {
        tile->state = CHEST;
        tile->stateData.chestItemTypeId = token - TOKEN_TREASURE_CHEST_0;
        return;
    }

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
        case TOKEN_ENEMY_SHROOM:
            tile->state = SHROOM;
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
    HUD * hud = ztgk::game::scene->systemManager.getSystem<HUD>();
    Group * menuGroup = hud->findGroupByName("Menu");
    Group * group = hud->findGroupByName("Load Screen");
    Sprite * loadingScreen = ztgk::game::scene->getChild("HUD")->getChildR("Load Screen")->getComponent<Sprite>();

    std::filesystem::directory_iterator dir("res/textures/loading_screens/");
    int num_scr = 0;
    for (auto & entry : dir) {
        if (entry.is_regular_file()) {
            num_scr++;
        }
    }
    auto rand = RNG::RandomInt(0, num_scr - 1);
    dir = std::filesystem::directory_iterator("res/textures/loading_screens/");
    for (auto & entry : dir) {
        if (entry.is_regular_file()) {
            if (rand == 0) {
                loadingScreen->load(entry.path().string());
                break;
            }
            rand--;
        }
    }
    menuGroup->setHidden(false);
    group->setHidden(false);

    auto signal = LoadSignal::signal();
    signal.callback = [path, group, menuGroup](){
        LevelSaving::loadImpl(path);
        group->setHidden(true);
        menuGroup->setHidden(true);
    };
    signal.time_to_live = 500; // short delay to allow the loading screen to render
    *ztgk::game::signalQueue += signal;
}

void LevelSaving::loadImpl(const string &path) {
    spdlog::info(std::format("Loading level from {}", path));
    auto grid = game::scene->systemManager.getSystem<Grid>();

    auto node = YAML::LoadFile(path);
    spdlog::trace("Clearing grid");
    grid->ClearWalls();
    grid->ClearAllWallData();
    spdlog::trace("Re-generating grid entities");
    grid->reinitWithSize({node["grid"]["width"].as<int>(), node["grid"]["height"].as<int>()});

    spdlog::trace("Reading grid layout to tile state");
    int z = 0;
    auto in = ifstream(path);
    string line;
    bool read = false;
    while ( getline(in, line) && line != TOKEN_LAYOUT_END && z < grid->height ) {
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
    ztgk::game::pranium_needed_to_win = 0;
    grid->InitializeTileEntities();
    grid->SetUpWalls();
    grid->UpdateFogData(grid->centerTile);

    //todo FIX LOAD EQUIPMENT
//    spdlog::trace("Reading node");
//    auto units = game::scene->systemManager.getSystem<UnitSystem>()->unitComponents;
//    if (!node["allies"]) {
//        spdlog::trace("No ally details - loading from generated level rather than save file.");
//    } else {
//        spdlog::trace("Loading unit equipment");
//        for (auto unode: node["allies"]) {
//            auto unit = std::find_if(units.begin(), units.end(), [unode](Unit * unit){ return unit->gridPosition == unode["gridPosition"].as<Vector2Int>(); });
//            if (unit == units.end()) {
//                spdlog::warn("Unit not found in generated units!");
//                continue;
//            }
//
//            (*unit)->equipment = unode["equipment"].as<UnitEquipment>();
//        }
//    }
    game::scene->systemManager.getSystem<WashingMachine>()->createWashingMachine(game::washingMachineModel);
    // todo chests and stuff, once relevant

    ztgk::game::scene->systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_game)->setHidden(false);
    spdlog::info("Finished loading");
}
