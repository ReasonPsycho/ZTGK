// 
// Created by igork on 08.06.2024. 
// 
 
#ifndef ZTGK_RNG_H 
#define ZTGK_RNG_H 
#include <random> 
 
class RNG { 
public: 
 
    static float RandomFloat(float min, float max) { 
        std::random_device rd; 
        std::mt19937 rng(rd()); 
        std::uniform_real_distribution<float> dist(min, max); 
        return dist(rng); 
    } 
 
    static int RandomInt(int min, int max) { 
        std::random_device rd; 
        std::mt19937 rng(rd()); 
        std::uniform_int_distribution<int> dist(min, max); 
        return dist(rng); 
    } 
 
    static bool RandomBool() { 
        std::random_device rd; 
        std::mt19937 rng(rd()); 
        std::uniform_int_distribution<int> dist(0, 1); 
        return dist(rng) == 1; 
    } 
 
private: 
 
}; 
 
 
#endif //ZTGK_RNG_H 
