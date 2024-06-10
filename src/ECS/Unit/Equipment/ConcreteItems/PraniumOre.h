// 
// Created by igork on 02.06.2024. 
// 
 
#ifndef ZTGK_PRANIUMORE_H 
#define ZTGK_PRANIUMORE_H 
#include "ECS/Unit/Equipment/Item.h" 
 
class PraniumOre : public Item{ 
public: 
    PraniumOre() : Item("Pranium Ore", "Magical, rare, valuable! Let's get cleaning!", false, ItemStats(1, 1, GridRange(1, 0)), false) { 
        std::string path = "res/models/pranium/pranium.fbx"; 
        model = new Model(&path); 
        model->loadModel(); 
    } 
 
}; 
 
#endif //ZTGK_PRANIUMORE_H 
