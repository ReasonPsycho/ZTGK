//
// Created by redkc on 09/01/2024.
//

#ifndef OPENGLGP_LIGHTSYSTEM_H
#define OPENGLGP_LIGHTSYSTEM_H


#include <vector>
#include <memory>
#include "glm/vec4.hpp"
#include "ILight.h"
#include "Lights/DirLight.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"
#include "Camera.h"
#include "modelLoading/Texture.h"
#include "Systems/RenderSystem/Lights/Shadows/Shadow.h"


class LightSystem {
public:
    //Setup
    LightSystem(Camera *camera);

    ~LightSystem();

    void Init();

    void PushToSSBO();

    void GenerateShadowBuffers(Shader *shader);
    
    //Add light
    void AddDirLight(glm::vec4 direction, glm::vec4 color);

    void AddPointLight(glm::vec4 position,
                       float constant,
                       float linear,
                       float quadratic,
                       glm::vec4 color);

    void AddSpotLight(glm::vec4 position,
                      glm::vec4 direction,
                      float cutOff,
                      float outerCutOff,
                      float constant,
                      float linear,
                      float quadratic,
                      glm::vec4 color);

    //Imgui
    void showLightTree();

    void GenerateShadows(void (*funcPtr)());
    
private:
    //Vectors
    std::vector<DirLight> dirLights;
    std::vector<PointLight> pointLights;
    std::vector<SpotLight> spotLights;
    std::vector<ILight *> lights;
    std::vector<std::shared_ptr<Shadow>> shadows;

    //Camera
    Camera *camera;

    //Shaders
    Shader simpleDepthShader = Shader("res/shaders/Shadows/point_shadows_depth.vert",
                                      "res/shaders/Shadows/point_shadows_depth.frag",
                                      "res/shaders/Shadows/point_shadows_depth.geom");
};


#endif //OPENGLGP_LIGHTSYSTEM_H
