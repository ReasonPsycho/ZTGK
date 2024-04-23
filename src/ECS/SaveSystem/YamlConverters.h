//
// Created by cheily on 23.04.2024.
//

#pragma once

#include "glm/ext/vector_int3.hpp"
#include "yaml-cpp/node/node.h"

namespace YAML {

template<>
struct convert<glm::ivec3> {
    static Node encode(const glm::ivec3& rhs) {
        Node node;
        node.push_back(rhs.x);
        node.push_back(rhs.y);
        node.push_back(rhs.z);
        return node;
    }

    static bool decode(const Node& node, glm::ivec3& rhs) {
        if ( !node.IsSequence() || node.size() != 3 ) {
            return false;
        }

        rhs.x = node[0].as<int>();
        rhs.y = node[1].as<int>();
        rhs.z = node[2].as<int>();
        return true;
    }
};



}