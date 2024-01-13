//
// Created by redkc on 09/01/2024.
//

#ifndef OPENGLGP_LIGHTSYSTEM_H
#define OPENGLGP_LIGHTSYSTEM_H


#include <vector>
#include "glm/vec4.hpp"


struct Light{
    glm::vec4 position;
    glm::vec4 color;
};

class LightSystem {
public:
    LightSystem(int size);
    void Init();
    
    int size;
    std::vector<Light> lights;
};


#endif //OPENGLGP_LIGHTSYSTEM_H
