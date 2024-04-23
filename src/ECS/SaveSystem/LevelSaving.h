//
// Created by cheily on 22.04.2024.
//

#pragma once

#include <string>
#include "ECS/Grid/Grid.h"
#include "Level.h"

namespace ztgk {
    const static std::string DEFAULT_SAVE_PATH = "save.txt";

    const static char TOKEN_ERROR = '\0';
    const static char TOKEN_FLOOR = ' ';
    const static char TOKEN_WALL = 'O';
    const static char TOKEN_PLAYER = '+';
    const static char TOKEN_ENEMY_BASIC = 'x';
    const static char TOKEN_TREASURE_CHEST = '*';
    const static char TOKEN_ORE = '^';
}

struct LevelSaving {

    static void save(Level level, const std::string& path = ztgk::DEFAULT_SAVE_PATH);
    static void load(std::string path = ztgk::DEFAULT_SAVE_PATH);

};
