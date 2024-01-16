//
// Created by redkc on 09/01/2024.
//

#ifndef OPENGLGP_LIGHTSYSTEM_H
#define OPENGLGP_LIGHTSYSTEM_H


#include <vector>
#include <memory>
#include "glm/vec4.hpp"
#include "Systems/LightSystem/Lights/DirLight.h"
#include "Systems/LightSystem/Lights/PointLight.h"
#include "Systems/LightSystem/Lights/SpotLight.h"


class LightSystem {
public:
    //Setup
    LightSystem();
    ~LightSystem();
    void PushToSSBO();
    
    //Add light
    void AddDirLight(glm::vec4  direction,glm::vec4 color);
    void AddPointLight(    glm::vec4  position,
    float constant,
    float linear,
    float quadratic,
    glm::vec4 color);
    void AddSpotLight(glm::vec4  position,
    glm::vec4  direction,
    float cutOff,
    float outerCutOff,
    float constant,
    float linear,
    float quadratic,
    glm::vec4 color);

    //Imgui
    void showLightTree();
    
private:
    //Vectors
    std::vector<DirLight> dirLights;
    std::vector<PointLight> pointLights;
    std::vector<SpotLight> spotLights;
    std::vector<std::shared_ptr<ILight>> lights;
};


#endif //OPENGLGP_LIGHTSYSTEM_H
