#include "ItemTypes.h"
#include "ECS/Utils/Util.h"
#include "ECS/Unit/Equipment/Item.h"
#include "ECS/Unit/Equipment/ConcreteItems/Hands.h"
#include "ECS/Unit/Equipment/ConcreteItems/Mop.h"
#include "ECS/Unit/Equipment/ConcreteItems/SuperMop.h"
#include "ECS/Unit/Equipment/ConcreteItems/WaterGun.h"
#include "ECS/Unit/Equipment/ConcreteItems/TestBuffItem.h"
#include "ECS/Unit/Equipment/ConcreteItems/PraniumOre.h"
#include "ECS/Unit/Equipment/ConcreteItems/Pendant.h"
#include "ECS/Unit/Equipment/ConcreteItems/Detergent.h"
#include "ECS/Unit/Equipment/ConcreteItems/Beacon.h"
#include "ECS/Unit/Equipment/ConcreteItems/Proszek.h"

using namespace ztgk;
#define quote(x) #x

s_item_types::s_item_types() {
    hands = 0;
    mop = 1;
    super_mop = 2;
    water_gun = 3;
    beacon = 4;
    test_buff_item = 5;
    detergent = 6;
    pendant = 7;
    pranium_ore = 8;
    proszek = 9;

    map = {};
    map.emplace(hands, quote(hands));
    map.emplace(mop, quote(mop));
    map.emplace(super_mop, quote(super_mop));
    map.emplace(water_gun, quote(water_gun));
    map.emplace(beacon, quote(beacon));
    map.emplace(test_buff_item, quote(test_buff_item));
    map.emplace(detergent, quote(detergent));
    map.emplace(pendant, quote(pendant));
    map.emplace(pranium_ore, quote(pranium_ore));
    map.emplace(proszek, quote(proszek));
}

unsigned s_item_types::id_of(Item *item) const {
    auto type = std::type_index(typeid(*item));

    if (type == std::type_index(typeid(Hands)))
        return hands;
    if (type == std::type_index(typeid(Mop)))
        return mop;
    if (type == std::type_index(typeid(SuperMop)))
        return super_mop;
    if (type == std::type_index(typeid(WaterGun)))
        return water_gun;
    if (type == std::type_index(typeid(Beacon)))
        return beacon;
    if (type == std::type_index(typeid(TestBuffItem)))
        return test_buff_item;
    if (type == std::type_index(typeid(Detergent)))
        return detergent;
    if (type == std::type_index(typeid(Pendant)))
        return pendant;
    if (type == std::type_index(typeid(PraniumOre)))
        return pranium_ore;
    if (type == std::type_index(typeid(Proszek)))
        return proszek;
}

std::string s_item_types::types_string() const {
    std::string ret;
    for (auto [id, name] : map) {
        ret += name + " - " + std::to_string(id) + '\n';
    }
    return ret;
}
