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
    glm::vec4 color;
    glm::vec4 position;
    float constant;
    float linear;
    float quadratic;
    float pointlessfloat;

    //Default constructor
    PointLightData(  glm::vec4 color = glm::vec4(glm::vec3 (255.0f),1),
    glm::vec4 position = glm::vec4(0.0f),
    float constant = 1,
    float linear = 1,
    float quadratic = 1)
            : color(color),
              position(position),
              constant(constant),
              linear(linear),
              quadratic(quadratic),
              pointlessfloat(0.0f)
    {}
};

class PointLight : public ILight {
public:
    PointLight(PointLightData data);
    
    PointLightData data;


    void showImGuiDetails(Camera *camera) override;
    
    void InnitShadow() override;

    void SetUpShadowBuffer(ShaderType shaderType,Shader* shadowMapShader,Shader* instanceShadowMapShader) override; // Pure virtual function
    void UpdateData() override;

private:
    std::vector<glm::mat4> shadowTransforms;
};


#endif //OPENGLGP_POINTLIGHT_H
