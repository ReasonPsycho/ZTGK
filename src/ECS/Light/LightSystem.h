//
// Created by redkc on 09/01/2024.
//

#ifndef OPENGLGP_LIGHTSYSTEM_H
#define OPENGLGP_LIGHTSYSTEM_H


#include "imgui.h"
#include <ImGuizmo.h>
#include "glad/glad.h"
#include <vector>
#include <memory>
#include "glm/vec4.hpp"
#include "Components/ILight.h"
#include "Components/DirLight.h"
#include "Components/PointLight.h"
#include "Components/SpotLight.h"
#include "Camera.h"
#include "modelLoading/Texture.h"
#include "../System.h"
#include "../Component.h"


class LightSystem : public System {
public:
    //Setup
    LightSystem(Camera *camera);

    ~LightSystem();

    void Init();

    void PushToSSBO();
    void Update(double deltaTime);

    void GenerateShadowBuffers();


    const std::type_index* getComponentTypes() override {return reinterpret_cast<const type_index *>(&componentTypes); };
    int getNumComponentTypes() override { return 4;};


    void addComponent(void* component) override;
    
    //Imgui
    void showLightTree();
    
    void PushDepthMapsToShader(Shader *shader);

    Shader instanceCubeDepthShader = Shader("res/shaders/Shadows/instance_point_shadows_depth.vert",
                                            "res/shaders/Shadows/point_shadows_depth.frag",
                                            "res/shaders/Shadows/point_shadows_depth.geom");

    Shader instancePlaneDepthShader = Shader("res/shaders/Shadows/instance_shadows_depth.vert",
                                             "res/shaders/Shadows/shadows_depth.frag");

    //Vectors
    std::vector<ILight *> lights;
    std::vector<DirLight*> dirLights;
    std::vector<PointLight*> pointLights;
    std::vector<SpotLight*> spotLights;


private:


    //Camera
    Camera *camera;

    //Shaders
    Shader cubeDepthShader = Shader("res/shaders/Shadows/point_shadows_depth.vert",
                                      "res/shaders/Shadows/point_shadows_depth.frag",
                                    "res/shaders/Shadows/point_shadows_depth.geom");   
    

    
    Shader planeDepthShader = Shader("res/shaders/Shadows/shadows_depth.vert",
                                     "res/shaders/Shadows/shadows_depth.frag");

    
    GLuint dirLightBufferId = 3;
    GLuint pointLightBufferId = 4;
    GLuint spotLightBufferId = 5;
    std::array<std::type_index, 4> componentTypes = {
            std::type_index(typeid(ILight)),
            std::type_index(typeid(DirLight)),
            std::type_index(typeid(PointLight)),
            std::type_index(typeid(SpotLight))
    };
};


#endif //OPENGLGP_LIGHTSYSTEM_H
