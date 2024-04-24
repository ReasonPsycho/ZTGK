//
// Created by cheily on 01.04.2024.
//

#pragma once

#include <string>
#include "imgui.h"
#include "spdlog/common.h"
#include "ImGuiSpdlogSink.h"

struct Entry {
    std::string text;
    spdlog::level::level_enum level;
};

class Console {
    std::vector<Entry> entries;
    ImGuiListClipper clipper;
    std::string name;
    bool scroll_down{true};
    std::shared_ptr<ImGuiSpdlogSink> sink;

public:
    using custom_menus_t = std::unordered_map<std::string, std::function<void()>>;
    custom_menus_t custom_menus;

    explicit Console(const std::string & name = "Console");
    explicit Console(const custom_menus_t & custom_menus, const std::string & name = "Console");

    void imguiWindow();
    void log(const Entry& entry);
    void log(const std::string & text, spdlog::level::level_enum severity = spdlog::level::info);
    void clear();

    spdlog::level::level_enum level();
    void level(spdlog::level::level_enum level);
};
