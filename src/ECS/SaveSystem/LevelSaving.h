//
// Created by cheily on 22.04.2024.
//

#pragma once

#include <string>
#include "ECS/Grid/Grid.h"
#include "Level.h"

namespace ztgk {
    const static std::string DEFAULT_SAVE_PATH = "save.txt";

    const static std::string TOKEN_LAYOUT_START = "# ---LAYOUT START---";
    const static char TOKEN_LAYOUT_LINE = '#';
    const static std::string TOKEN_LAYOUT_END = "# ---LAYOUT END---";

    const static char TOKEN_ERROR = '\0';
    const static char TOKEN_FLOOR = ' ';
    const static char TOKEN_WALL = 'O';
    const static char TOKEN_PLAYER = '+';
    const static char TOKEN_ENEMY_BASIC = 'x';
    const static char TOKEN_TREASURE_CHEST = '*';
    const static char TOKEN_ORE = '^';

    // todo match with tile state enum
    enum SAVE_TOKEN : char {
        ERROR = '\0',
    };
}

struct LevelSaving {

    static void save(Level from, const std::string& path = ztgk::DEFAULT_SAVE_PATH);
    static void load(Level & to, const std::string& path = ztgk::DEFAULT_SAVE_PATH);

};
