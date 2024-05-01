//
// Created by cheily on 23.04.2024.
//

#pragma once
#define quote(x) #x

#include "glm/ext/vector_int3.hpp"
#include <yaml-cpp/yaml.h>
#include "ECS/Unit/Unit.h"
#include "ECS/Utils/Globals.h"

inline std::string nameof(const std::string & full_name) {
    auto pos = full_name.find_last_of('.');
    if (pos == std::string::npos) pos = full_name.find_last_of(':');
    return full_name.substr(pos + 1);
}


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

template<>
struct convert<Vector2Int> {
    static Node encode(const Vector2Int& rhs) {
        Node node;
        node.push_back(rhs.x);
        node.push_back(rhs.z);
        return node;
    }

    static bool decode(const Node& node, Vector2Int& rhs) {
        rhs.x = node[0].as<int>();
        rhs.z = node[1].as<int>();
        return true;
    }
};

template<>
struct convert<ItemStats> {
    static Node encode(const ItemStats& rhs) {
        Node node;
        node[nameof(quote(rhs.addHealth))] = rhs.addHealth;
        node[nameof(quote(rhs.addAttackDamage))] = rhs.addAttackDamage;
        node[nameof(quote(rhs.addAttackSpeed))] = rhs.addAttackSpeed;
        node[nameof(quote(rhs.addMovementSpeed))] = rhs.addMovementSpeed;
        node[nameof(quote(rhs.addRange))] = rhs.addRange;
        return node;
    }

    static bool decode(const Node& node, ItemStats& rhs) {
        rhs.addHealth = node[nameof(quote(rhs.addHealth))].as<float>();
        rhs.addAttackDamage = node[nameof(quote(rhs.addAttackDamage))].as<float>();
        rhs.addAttackSpeed = node[nameof(quote(rhs.addAttackSpeed))].as<float>();
        rhs.addMovementSpeed = node[nameof(quote(rhs.addMovementSpeed))].as<float>();
        rhs.addRange = node[nameof(quote(rhs.addRange))].as<float>();
        return true;
    }
};

template<>
struct convert<Item> {
    static Node encode(const Item& rhs) {
        Node node;
        node["typeId"] = "TODO";
        node[nameof(quote(rhs.name))] = rhs.name;
        node[nameof(quote(rhs.desctiption))] = rhs.desctiption;
        node[nameof(quote(rhs.stats))] = rhs.stats;
        node[nameof(quote(rhs.takesTwoSlots))] = rhs.takesTwoSlots;
        return node;
    }

    static bool decode(const Node& node, Item& rhs) {
        rhs.name = node[nameof(quote(rhs.name))].as<std::string>();
        rhs.desctiption = node[nameof(quote(rhs.desctiption))].as<std::string>();
        rhs.stats = node[nameof(quote(rhs.stats))].as<ItemStats>();
        rhs.takesTwoSlots = node[nameof(quote(rhs.takesTwoSlots))].as<bool>();
        return true;
    }
};

template<>
struct convert<UnitEquipment> {
    static Node encode(const UnitEquipment& rhs) {
        Node node;
        if ( rhs.item1 == nullptr )
            node[nameof(quote(rhs.item1))] = YAML::Null;
        else node[nameof(quote(rhs.item1))] = *rhs.item1;
        if ( rhs.item2 == nullptr )
            node[nameof(quote(rhs.item2))] = YAML::Null;
        else node[nameof(quote(rhs.item2))] = *rhs.item2;
        return node;
    }

    static bool decode(const Node& node, UnitEquipment& rhs) {
        // todo this when items are real
        rhs.item1 = nullptr;
        rhs.item2 = nullptr;
//        if ( node[nameof(quote(rhs.item1))].IsNull() )
//            rhs.item1 = nullptr;
//        else rhs.item1 = node[nameof(quote(rhs.item1))].as<Item>();
        return true;
    }
};

template<>
struct convert<UnitStats> {
        static Node encode(const UnitStats& rhs) {
            Node node;
            node[nameof(quote(rhs.health))] = rhs.health;
            node[nameof(quote(rhs.attackDamage))] = rhs.attackDamage;
            node[nameof(quote(rhs.attackSpeed))] = rhs.attackSpeed;
            node[nameof(quote(rhs.movementSpeed))] = rhs.movementSpeed;
            node[nameof(quote(rhs.range))] = rhs.range;
            return node;
        }

        static bool decode(const Node& node, UnitStats& rhs) {
            rhs.health = node[nameof(quote(rhs.health))].as<float>();
            rhs.attackDamage = node[nameof(quote(rhs.attackDamage))].as<float>();
            rhs.attackSpeed = node[nameof(quote(rhs.attackSpeed))].as<float>();
            rhs.movementSpeed = node[nameof(quote(rhs.movementSpeed))].as<float>();
            rhs.range = node[nameof(quote(rhs.range))].as<float>();
            return true;
        }
    };

template<>
struct convert<Unit> {
    static Node encode(const Unit & rhs) {
        Node node;
        node[nameof(quote(rhs.name))] = rhs.name;
        node[nameof(quote(rhs.gridPosition))] = rhs.gridPosition;
        node[nameof(quote(rhs.isAlly))] = rhs.isAlly;
        node[nameof(quote(rhs.baseStats))] = rhs.baseStats;
        node[nameof(quote(rhs.equipment))] = rhs.equipment;
        return node;
    }

    static bool decode(const Node & node, Unit & rhs) {
        rhs.name = node[nameof(quote(rhs.name))].as<std::string>();
        rhs.gridPosition = node[nameof(quote(rhs.gridPosition))].as<Vector2Int>();
        rhs.isAlly = node[nameof(quote(rhs.isAlly))].as<bool>();
        rhs.baseStats = node[nameof(quote(rhs.baseStats))].as<UnitStats>();
        rhs.equipment = node[nameof(quote(rhs.equipment))].as<UnitEquipment>();
        rhs.serializer_init(ztgk::game::scene->systemManager.getSystem<Grid>());
        return true;
    }
};

}