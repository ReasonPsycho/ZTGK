//
// Created by cheily on 22.04.2024.
//

#include "YamlConverters.h"
#include "LevelSaving.h"
#include <yaml-cpp/yaml.h>

using namespace ztgk;

void LevelSaving::save(Level from, const std::string& path) {
    auto thr = std::thread([from, path](){
        spdlog::trace(std::format("Saving from to {}", path));
        YAML::Node node;
        std::string layout{TOKEN_LAYOUT_START + '\n'};

        spdlog::trace("Serializing grid");
        char token;
        for (int x = 0; x < from.grid->width; ++x) {
            layout += TOKEN_LAYOUT_LINE;
            for (int z = 0; z < from.grid->height; ++z) {
                auto tile = from.grid->getTileAt(x, z);

                if ( tile == nullptr ) token = TOKEN_ERROR;
                else if ( tile->isFloor ) token = TOKEN_FLOOR;
                else token = TOKEN_WALL;

                layout += token;
            }
            layout += '\n';
        }
        layout += TOKEN_LAYOUT_END + '\n';

        spdlog::trace("Serializing units");
        node["units"].SetStyle(YAML::EmitterStyle::Flow);
        for (auto & unit : from.units) {
            node["units"].push_back(unit);
        }

        std::ofstream out = std::ofstream(path);
        spdlog::trace("Writing layout");
        out << layout << '\n';
        spdlog::trace("Writing node");
        out << node;
        spdlog::trace("Save complete");
    });
    thr.detach();
}

void LevelSaving::load(Level & to, const std::string& path) {
    auto thr = std::thread([path, to](){
        spdlog::trace(std::format("Loading level from {}", path));

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
            for (char c : line) {
                spdlog::trace(std::format("Reading tile x{} z{} : {}", x, z, c));
                auto tile = to.grid->getTileAt(x, z);

                if ( c == TOKEN_FLOOR ) {
                    tile->isFloor = true;
                    tile->vacant = true;
                }
                else if ( c == TOKEN_WALL ) {
                    tile->isFloor = false;
                    tile->vacant = false;
                }
                ++x;
                if ( x == to.grid->width ) x = 0;
            }

            ++z;
        }

        spdlog::trace("Reading node");

        spdlog::trace("Finished loading");

    });
    thr.detach();
}
