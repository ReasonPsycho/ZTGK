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

    virtual void
    SetUpShadowBuffer(Shader *shadowMapShader, Shader *instanceShadowMapShader, int width, int height,
                      GLuint ShadowMapArrayId, int index) = 0; // Pure virtual function
    virtual void Innit(int width, int height, int index) = 0;
    virtual void UpdateData(int height, int width) = 0;
    unsigned int depthMap{};
    void DeleteShadow();


protected:
    int uniqueID;     // Instance variable to store the unique ID for each object
    bool initializedShadow = false;
    unsigned int depthMapFBO{};

    //For shadows
    glm::mat4 shadowProj{};
};

#endif //OPENGLGP_ILIGHT_H
