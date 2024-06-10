// 
// Created by igork on 25.03.2024. 
// 
 
#ifndef EQUIPMENT_H 
#define EQUIPMENT_H 
#include "Item.h" 
 
 
class UnitEquipment { 
public: 
    Unit * unit; 
 
    // default, no item 
    Item* item0; 
    GridRange rangeEff0; 
    [[nodiscard]] bool use_default() const; 
 
    Item* item1; 
    GridRange rangeEff1; 
 
    Item* item2; 
    GridRange rangeEff2; 
 
    float cd_between_max_sec = 0.5; 
    float cd_between_sec = 0; 
 
    explicit UnitEquipment(Unit * unit); 
 
    // purely for ptr management, do not use outside of InventoryManager 
    std::pair<Item *, Item *> equipItem(Item* item, short slot); 
    // purely for ptr management, do not use outside of InventoryManager 
    Item * unequipItem(short slot); 
 
    [[nodiscard]] bool is_full() const; 
    [[nodiscard]] Item * in_range_of(glm::ivec2 self, glm::ivec2 target) const; 
 
    // serializer 
    UnitEquipment() {}; 
 
    void imgui_preview() const; 
 
    Item * operator[](const short & slot) const { 
        switch (slot) { 
            case 0: 
                return item0; 
            case 1: 
                return item1; 
            case 2: 
                return item2; 
            default: 
                spdlog::error("Accessing incorrect unit equipment slot {}!", slot); 
                return nullptr; 
        } 
    } 
    GridRange * range_of(const short & slot) { 
        switch (slot) { 
            case 0: 
                return &rangeEff0; 
            case 1: 
                return &rangeEff1; 
            case 2: 
                return &rangeEff2; 
            default: 
                spdlog::error("Accessing grid range for incorrect unit equipment slot {}!", slot); 
                return nullptr; 
        } 
    } 
    bool has(Item * item) { 
        return item0 == item || item1 == item || item2 == item; 
    } 
}; 
 
 
 
#endif //EQUIPMENT_H 
