//
// Created by redkc on 09/01/2024.
//

#ifndef OPENGLGP_LIGHTSYSTEM_H
#define OPENGLGP_LIGHTSYSTEM_H


#include <vector>
#include "glm/vec4.hpp"


struct DirLight {
    glm::vec4  direction;
    glm::vec4 color;
};

struct PointLight {
    glm::vec4  position;

    float constant;
    float linear;
    float quadratic;
    float pointlessfloat;

    glm::vec4 color;
};

struct SpotLight {
    glm::vec4  position;
    glm::vec4  direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
    float pointlessfloat;
    float pointlessfloat2;
    float pointlessfloat3;

    glm::vec4 color;
};


class LightSystem {
public:
    LightSystem();
    void Init();
    
    std::vector<DirLight> dirLights;
    std::vector<PointLight> pointLights;
    std::vector<SpotLight> spotLights;
};


#endif //OPENGLGP_LIGHTSYSTEM_H
