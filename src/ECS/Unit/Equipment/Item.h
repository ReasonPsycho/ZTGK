//
// Created by igork on 25.03.2024.
//

#ifndef ITEM_H
#define ITEM_H
#include <string>
#include "Modifiers.h"
#include "GridRange.h"
#include "ConcreteItems/ItemTypes.h"

struct ItemStats {
    float dmg{0};
    float cd_max_sec{1};
    GridRange range{};
    // ability

    Modifiers add_to_unit{};
};

class Item {
public:
    static const s_item_types item_types;

    unsigned uniqueID;

    bool offensive{false};
    float cd_sec{0};

    // bool on_ground{false};
    // glm::vec2 worldPos{};

    std::string name;
    std::string icon_path = "res/textures/question_mark.png";
    std::string description;
    ItemStats stats{};
    bool takesTwoSlots;
    Model * model;

    std::unordered_map<std::string, std::string> highlight_passive_stats = {};

    Item(std::string name, std::string description, bool offensive, ItemStats stats, bool takesTwoSlots = false, Model * model = ztgk::game::mopModel);

    void imgui_preview() const;
};



#endif //ITEM_H
