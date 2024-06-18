//
// Created by cheily on 22.04.2024.
//

#pragma once

#include <string>
#include "ECS/Grid/Tile.h"

namespace ztgk {
    const static std::string DEFAULT_SAVE_PATH = "save.txt";

    const static std::string TOKEN_LAYOUT_START = "# ---LAYOUT START---";
    const static char TOKEN_LAYOUT_LINE = '#';
    const static std::string TOKEN_LAYOUT_END = "# ---LAYOUT END---";

    const static char TOKEN_ERROR = '\0';
    const static char TOKEN_FLOOR = ' ';
    const static char TOKEN_WALL = 'O';
    const static char TOKEN_TREASURE_CHEST = '*';
    const static char TOKEN_TREASURE_CHEST_0 = '0';
    const static char TOKEN_TREASURE_CHEST_1 = '1';
    const static char TOKEN_TREASURE_CHEST_2 = '2';
    const static char TOKEN_TREASURE_CHEST_3 = '3';
    const static char TOKEN_TREASURE_CHEST_4 = '4';
    const static char TOKEN_TREASURE_CHEST_5 = '5';
    const static char TOKEN_TREASURE_CHEST_6 = '6';
    const static char TOKEN_TREASURE_CHEST_7 = '7';
    const static char TOKEN_TREASURE_CHEST_8 = '8';
    const static char TOKEN_TREASURE_CHEST_9 = '9';
    const static char TOKEN_CORE = 'c';
    const static char TOKEN_ORE = '^';
    const static char TOKEN_PLAYER = '+';
    const static char TOKEN_ENEMY_BUG = 'x';
    const static char TOKEN_ENEMY_SHROOM = 's';

    char tile_state_to_token(TileState state, TileStateData data = {});
    void tile_state_from_token(char token, Tile * tile);
}

struct LevelSaving {
    static char* im_path;

    static void save(const std::string& path = ztgk::DEFAULT_SAVE_PATH);
    static void load( const std::string& path = ztgk::DEFAULT_SAVE_PATH);

    static void loadImpl(const string &path);
};
