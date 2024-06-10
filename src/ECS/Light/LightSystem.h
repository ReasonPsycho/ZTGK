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
#include "../System.h" 
#include "../Component.h" 
#include "ECS/Scene.h" 
#include <algorithm> 
 
 
class LightSystem : public System { 
public: 
    //Setup 
    LightSystem(Camera *camera,Scene* scene); 
 
    ~LightSystem(); 
 
    void Init(); 
 
    void PushToSSBO(); 
    void UpdateImpl() override; 
 
    void GenerateShadowBuffers(); 
 
 
    const std::type_index* getComponentTypes() override {return reinterpret_cast<const std::type_index *>(&componentTypes); }; 
    int getNumComponentTypes() override { return 4;}; 
 
 
    void addComponent(void* component) override; 
    void removeComponent(void* component) override; 
    void createPlaneShadowMap(); 
    void createCubeShadowMap(); 
    void PushDepthMapsToShader(Shader *shader); 
    void showImGuiDetailsImpl(Camera *camera); 
    void registerComponents() override{ 
        systemManager->registerComponent<DirLight>(); 
        systemManager->registerComponent<PointLight>(); 
        systemManager->registerComponent<SpotLight>(); 
    } 
 
     
    //Vectors 
    std::vector<ILight *> lights; 
    std::vector<DirLight*> dirLights; 
    std::vector<PointLight*> pointLights; 
    std::vector<SpotLight*> spotLights; 
private: 
    //Camera 
    Camera *camera; 
    Scene *scene; 
    bool isDataPushedToSSBO = false; 
    //Shaders 
    Shader cubeDepthShader = Shader("res/shaders/Shadows/point_shadows_depth.vert", 
                                      "res/shaders/Shadows/point_shadows_depth.frag"); 
     
    Shader planeDepthShader = Shader("res/shaders/Shadows/shadows_depth.vert", 
                                     "res/shaders/Shadows/shadows_depth.frag"); 
 
    Shader instanceCubeDepthShader = Shader("res/shaders/Shadows/instance_point_shadows_depth.vert", 
                                            "res/shaders/Shadows/point_shadows_depth.frag"); 
 
    Shader instancePlaneDepthShader = Shader("res/shaders/Shadows/instance_shadows_depth.vert", 
                                             "res/shaders/Shadows/shadows_depth.frag"); 
 
    int CUBE_SHADOW_INDEX = 8; 
    int PLANE_SHADOW_TEXTURE_INDEX = 9; 
    unsigned int depthFBO{}; 
     
 
    GLuint dirLightBufferBindingPoint = 3; 
    GLuint pointLightBufferBindingPoint = 4; 
    GLuint spotLightBufferBindingPoint = 5; 
 
    GLuint dirLightBufferId; 
    GLuint pointLightBufferId; 
    GLuint spotLightBufferId; 
 
    GLuint planeShadowMaps; 
    GLuint cubeShadowMaps; 
 
    int maxDirLight = 1; 
    int maxPointLight = 20; 
    int maxSpotLight = 20; 
 
 
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024; 
 
    std::array<std::type_index, 4> componentTypes = { 
            std::type_index(typeid(ILight)), 
            std::type_index(typeid(DirLight)), 
            std::type_index(typeid(PointLight)), 
            std::type_index(typeid(SpotLight)) 
    }; 
 
 
    GLubyte whitePixel[3] = {255, 255, 255}; 
    GLubyte *whiteImage = new GLubyte[SHADOW_WIDTH * SHADOW_HEIGHT * 3]; 
    float borderColor[4] = {1.0, 1.0, 1.0, 1.0}; 
 
}; 
 
 
#endif //OPENGLGP_LIGHTSYSTEM_H 
