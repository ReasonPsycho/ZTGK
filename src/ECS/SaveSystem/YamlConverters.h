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
struct convert<GridRange> { 
    static Node encode(const GridRange& rhs) { 
        Node node; 
        node[nameof(quote(rhs.add))] = rhs.add; 
        node[nameof(quote(rhs.remove))] = rhs.remove; 
        return node; 
    } 
 
    static bool decode(const Node& node, GridRange& rhs) { 
        auto add = node[nameof(quote(rhs.add))].as<int>(); 
        auto rem = node[nameof(quote(rhs.remove))].as<int>(); 
        rhs = GridRange(add, rem); 
        return true; 
    } 
}; 
 
template<> 
struct convert<Modifiers> { 
    static Node encode(const Modifiers& rhs) { 
        Node node; 
        node[nameof(quote(rhs.max_hp))] = rhs.max_hp; 
        node[nameof(quote(rhs.def_flat))] = rhs.def_flat; 
        node[nameof(quote(rhs.dmg_perc))] = rhs.dmg_perc; 
        node[nameof(quote(rhs.dmg_flat))] = rhs.dmg_flat; 
        node[nameof(quote(rhs.move_speed))] = rhs.move_speed; 
        node[nameof(quote(rhs.mine_speed))] = rhs.mine_speed; 
        node[nameof(quote(rhs.atk_speed))] = rhs.atk_speed; 
        node[nameof(quote(rhs.knockback))] = rhs.knockback; 
        return node; 
    } 
 
    static bool decode(const Node& node, Modifiers& rhs) { 
        rhs.max_hp = node[nameof(quote(rhs.max_hp))].as<float>(); 
        rhs.def_flat = node[nameof(quote(rhs.def_flat))].as<float>(); 
        rhs.dmg_perc = node[nameof(quote(rhs.dmg_perc))].as<float>(); 
        rhs.dmg_flat = node[nameof(quote(rhs.dmg_flat))].as<float>(); 
        rhs.move_speed = node[nameof(quote(rhs.move_speed))].as<float>(); 
        rhs.mine_speed = node[nameof(quote(rhs.mine_speed))].as<float>(); 
        rhs.atk_speed = node[nameof(quote(rhs.atk_speed))].as<float>(); 
        rhs.knockback = node[nameof(quote(rhs.knockback))].as<int>(); 
        return true; 
    } 
}; 
 
template<> 
struct convert<ItemStats> { 
    static Node encode(const ItemStats& rhs) { 
        Node node; 
        node[nameof(quote(rhs.dmg))] = rhs.dmg; 
        node[nameof(quote(rhs.cd_max_sec))] = rhs.cd_max_sec; 
        node[nameof(quote(rhs.range))] = rhs.range; 
        node[nameof(quote(rhs.add_to_unit))] = rhs.add_to_unit; 
        return node; 
    } 
 
    static bool decode(const Node& node, ItemStats& rhs) { 
        rhs.dmg = node[nameof(quote(rhs.dmg))].as<float>(); 
        rhs.cd_max_sec = node[nameof(quote(rhs.cd_max_sec))].as<float>(); 
        rhs.range = node[nameof(quote(rhs.range))].as<GridRange>(); 
        rhs.add_to_unit = node[nameof(quote(rhs.add_to_unit))].as<Modifiers>(); 
        return true; 
    } 
}; 
 
template<> 
struct convert<Item> { 
    static Node encode(const Item& rhs) { 
        Node node; 
        node["typeId"] = "TODO"; 
        node[nameof(quote(rhs.name))] = rhs.name; 
        node[nameof(quote(rhs.description))] = rhs.description; 
        node[nameof(quote(rhs.stats))] = rhs.stats; 
        node[nameof(quote(rhs.takesTwoSlots))] = rhs.takesTwoSlots; 
        return node; 
    } 
 
    static bool decode(const Node& node, Item& rhs) { 
        rhs.name = node[nameof(quote(rhs.name))].as<std::string>(); 
        rhs.description = node[nameof(quote(rhs.description))].as<std::string>(); 
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
        node[nameof(quote(rhs.max_hp))] = rhs.max_hp; 
        node[nameof(quote(rhs.hp))] = rhs.hp; 
        node[nameof(quote(rhs.move_spd))] = rhs.move_spd; 
        node[nameof(quote(rhs.mine_spd))] = rhs.mine_spd; 
        node[nameof(quote(rhs.added))] = rhs.added; 
        return node; 
    } 
 
    static bool decode(const Node& node, UnitStats& rhs) { 
        rhs.max_hp = node[nameof(quote(rhs.max_hp))].as<float>(); 
        rhs.hp = node[nameof(quote(rhs.hp))].as<float>(); 
        rhs.move_spd = node[nameof(quote(rhs.move_spd))].as<float>(); 
        rhs.mine_spd = node[nameof(quote(rhs.mine_spd))].as<float>(); 
        rhs.added = node[nameof(quote(rhs.added))].as<Modifiers>(); 
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
        node[nameof(quote(rhs.stats))] = rhs.stats; 
        node[nameof(quote(rhs.equipment))] = rhs.equipment; 
        return node; 
    } 
 
    static bool decode(const Node & node, Unit & rhs) { 
        rhs.name = node[nameof(quote(rhs.name))].as<std::string>(); 
        rhs.gridPosition = node[nameof(quote(rhs.gridPosition))].as<Vector2Int>(); 
        rhs.isAlly = node[nameof(quote(rhs.isAlly))].as<bool>(); 
        rhs.stats = node[nameof(quote(rhs.base))].as<UnitStats>(); 
        rhs.equipment = node[nameof(quote(rhs.equipment))].as<UnitEquipment>(); 
        rhs.serializer_init(ztgk::game::scene->systemManager.getSystem<Grid>()); 
        return true; 
    } 
}; 
 
} 
