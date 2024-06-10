// 
// Created by igork on 24.03.2024. 
// 
 
#ifndef IMINEABLE_H 
#define IMINEABLE_H 
 
 
#include "ECS/Component.h" 
#include "ECS/Utils/VectorUtils.h" 
#include "ECS/Grid/Grid.h" 
 
class IMineable : public Component{ 
public: 
    IMineable(IMineable *pMineable); 
 
    float timeToMine; 
    Vector2Int gridPosition; 
    Grid* grid; 
    explicit  IMineable(float timeToMine, Vector2Int gridPosition, Grid* grid); 
    ~IMineable(); 
    virtual void onMine(Unit * unit) { /*todo fire particles!*/ }; 
    virtual void onMined(Unit * unit) { /**/ }; 
    void Mine(Unit * unit); 
 
    void UpdateImpl() override; 
 
    void showImGuiDetailsImpl(Camera *camera) override; 
 
    float getTimeToMineRemaining() const { 
        return timeToMineRemaining; 
    } 
    bool isMined = false; 
 
protected: 
    float timeToMineRemaining; 
}; 
 
 
 
#endif //IMINEABLE_H 
