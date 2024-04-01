//
// Created by redkc on 16/01/2024.
//

#ifndef OPENGLGP_ILIGHT_H
#define OPENGLGP_ILIGHT_H

#include "ECS/Component.h"
#include "ECS/Render/ModelLoading/Shader.h"
#include "ECS/Render/Camera/Camera.h"


enum LightType {
    Directional,
    Spot,
    Point,
};

enum ShaderType {
    Instance,
    Normal,
};

class ILight : public Component {
public:
    ILight();

    ~ILight();

    enum LightType lightType;


    virtual void showImGuiDetails(Camera *camera) = 0; // Pure virtual function

    virtual void SetUpShadowBuffer(ShaderType shaderType, Shader *shadowMapShader,
                                   Shader *instanceShadowMapShader) = 0; // Pure virtual function
    virtual void InnitShadow() = 0;
    virtual void UpdateData() = 0;

    void DeleteShadow();

    unsigned int depthMap{};
    
protected:
    int uniqueID;     // Instance variable to store the unique ID for each object

    //For shadows
    bool initializedShadow = false;
    unsigned int depthMapFBO{};
    const unsigned int SHADOW_WIDTH = 512, SHADOW_HEIGHT = 512;
    glm::mat4 shadowProj{};
};

#endif //OPENGLGP_ILIGHT_H
