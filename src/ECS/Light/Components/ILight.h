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


    virtual void showImGuiDetailsImpl(Camera *camera) = 0; // Pure virtual function

    virtual void
    SetUpShadowBuffer(Shader *shadowMapShader, GLuint ShadowMapArrayId, int index, int layer) = 0; // Pure virtual function
    virtual void Innit(int width, int height, int index) = 0;
    virtual void UpdateData(int height, int width) = 0;
    void DeleteShadow();
    bool isActive = true;

protected:
    bool initializedShadow = false;

    //For shadows
    glm::mat4 shadowProj{};
};

#endif //OPENGLGP_ILIGHT_H
