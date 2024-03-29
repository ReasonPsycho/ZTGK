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
    glm::vec4 color;
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
    glm::mat4x4 lightSpaceMatrix;

    SpotLightData( glm::vec4 color = glm::vec4(glm::vec3 (255.0f),1),
    glm::vec4 position = glm::vec4(0.0f),
    glm::vec4 direction= glm::vec4(1.0f),
    float cutOff = 1,
    float outerCutOff = 1,
    float constant = 1,
    float linear = 1,
    float quadratic = 1,
    glm::mat4x4 lightSpaceMatrix = glm::mat4x4(1.0f)
    )
            : color(color),
              position(position),
              direction(direction),
              cutOff(cutOff),
              outerCutOff(outerCutOff),
              constant(constant),
              linear(linear),
              quadratic(quadratic),
              pointlessfloat(0.0f),
              pointlessfloat2(0.0f),
              pointlessfloat3(0.0f),
              lightSpaceMatrix(lightSpaceMatrix) // set to identity matrix
    {}
};

class SpotLight : public ILight {
private:
    float near_plane = 1.0f, far_plane = 25.0f;

public:
    SpotLight(SpotLightData data);



    SpotLightData data;

    void showImGuiDetails(Camera *camera) override;
    
    void InnitShadow() override;

    void SetUpShadowBuffer(ShaderType shaderType,Shader* shadowMapShader,Shader* instanceShadowMapShader) override; // Pure virtual function
    void UpdateData() override;

};


#endif //OPENGLGP_SPOTLIGHT_H
