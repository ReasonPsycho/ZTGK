//
// Created by igork on 24.03.2024.
//

#ifndef IMINEABLE_H
#define IMINEABLE_H


#include "ECS/Component.h"

class IMineable : public Component{
public:
    float timeToMine;
    explicit  IMineable(float timeToMine);
    ~IMineable() = default;
    void Mine();

    void Update() override;

    void showImGuiDetails(Camera *camera) override;

private:
    float timeToMineRemaining;
};



#endif //IMINEABLE_H
