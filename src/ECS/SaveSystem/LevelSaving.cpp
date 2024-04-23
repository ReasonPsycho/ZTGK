//
// Created by cheily on 22.04.2024.
//

#include "YamlConverters.h"
#include "LevelSaving.h"
#include <yaml-cpp/yaml.h>

using namespace ztgk;

void LevelSaving::save(Level level, const std::string& path) {
    auto thr = std::thread([level, path](){
        spdlog::trace(std::format("Saving level to {}", path));
        YAML::Node node;
        std::string layout{'#'};

        spdlog::trace("Serializing grid");
        char token;
        for (int x = 0; x < level.grid->width; ++x) {
            for (int z = 0; z < level.grid->height; ++z) {
                auto tile = level.grid->getTileAt(x, z);

                if ( tile == nullptr ) token = TOKEN_ERROR;
                else if ( tile->isFloor ) token = TOKEN_FLOOR;
                else token = TOKEN_WALL;

                layout += token;
            }
            layout += "\n#";
        }

        spdlog::trace("Serializing units");
        node["units"].SetStyle(YAML::EmitterStyle::Flow);
        for (auto & unit : level.units) {
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

void LevelSaving::load(std::string path) {

}
