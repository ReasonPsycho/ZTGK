//
// Created by redkc on 16/01/2024.
//

#ifndef OPENGLGP_POINTLIGHT_H
#define OPENGLGP_POINTLIGHT_H



#include <imgui.h>
#include <ImGuizmo.h>
#include "glm/vec4.hpp"
#include "imgui.h"
#include "ILight.h"


struct PointLightData {
    glm::vec4 position;

    float constant;
    float linear;
    float quadratic;
    float pointlessfloat;

    glm::vec4 color;
};

class PointLight : public ILight {
public:
    PointLight(PointLightData data);
    
    PointLightData data;


    void showImGuiDetails(Camera *camera) override;

    void EditLight(Camera *camera) override;

    void InnitShadow() override;

    void SetUpShadowBuffer(ShaderType shaderType,Shader* shadowMapShader,Shader* instanceShadowMapShader) override; // Pure virtual function

private:
    std::vector<glm::mat4> shadowTransforms;
};


#endif //OPENGLGP_POINTLIGHT_H
