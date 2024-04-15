//
// Created by cheily on 01.04.2024.
//

#pragma once

#include <string>
#include "imgui.h"
#include "spdlog/common.h"

struct Entry {
    std::string text;
    spdlog::level::level_enum level;
};

class Console {
    std::vector<Entry> entries;
    ImGuiListClipper clipper;

public:
    Console();
    void imguiWindow();
    void log(const Entry& entry);
    void log(const std::string & text, spdlog::level::level_enum severity);
    void clear();
};
