//
// Created by igork on 24.03.2024.
//

#ifndef IMINEABLE_H
#define IMINEABLE_H



class IMineable {
public:
    float timeToMine;
    explicit  IMineable(float timeToMine);
    ~IMineable() = default;
    void Mine();

private:
    float timeToMineRemaining;
};



#endif //IMINEABLE_H
