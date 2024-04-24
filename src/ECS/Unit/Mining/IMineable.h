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
    float timeToMine;
    Vector2Int gridPosition;
    Grid* grid;
    explicit  IMineable(float timeToMine, Vector2Int gridPosition, Grid* grid);
    ~IMineable() = default;
    void Mine();

    void Update() override;

    void showImGuiDetails(Camera *camera) override;

    float getTimeToMineRemaining() const {
        return timeToMineRemaining;
    }

private:
    float timeToMineRemaining;
};



#endif //IMINEABLE_H
