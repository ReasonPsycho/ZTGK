//
// Created by redkc on 16/01/2024.
//

#ifndef OPENGLGP_SPOTLIGHT_H
#define OPENGLGP_SPOTLIGHT_H


#include "imgui.h"
#include <ImGuizmo.h>
#include "glm/vec4.hpp"
#include "ILight.h"
#include "glm/gtx/quaternion.hpp"

struct SpotLightData {
    glm::vec4 position;
    glm::vec4 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
    float pointlessfloat;
    float pointlessfloat2;
    float pointlessfloat3;

    glm::vec4 color;
    glm::mat4x4 lightSpaceMatrix;
};

class SpotLight : public ILight {
public:
    SpotLight(SpotLightData data);



    SpotLightData data;

    void showImGuiDetails(Camera *camera) override;
    
    void InnitShadow() override;

    void SetUpShadowBuffer(ShaderType shaderType,Shader* shadowMapShader,Shader* instanceShadowMapShader) override; // Pure virtual function
    void UpdateData() override;

};


#endif //OPENGLGP_SPOTLIGHT_H
