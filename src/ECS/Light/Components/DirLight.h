//
// Created by redkc on 16/01/2024.
//

#ifndef OPENGLGP_DIRLIGHT_H
#define OPENGLGP_DIRLIGHT_H


#include "imgui.h"
#include <ImGuizmo.h>
#include "glm/vec4.hpp"
#include "ILight.h"
#include "glm/gtx/quaternion.hpp"

struct DirLightData {
    glm::vec4 direction;
    glm::vec4 color;
    glm::vec4 position; // yeah i know but we don't really use it until later
    glm::mat4x4 lightSpaceMatrix;
};

class DirLight : public ILight {
public:
    DirLight( DirLightData data);
    

    DirLightData data;

    void showImGuiDetails(Camera *camera) override;

    
    void InnitShadow() override;

    void SetUpShadowBuffer(ShaderType shaderType,Shader* shadowMapShader,Shader* instanceShadowMapShader) override; // Pure virtual function


    void UpdateData() override;
};

#endif //OPENGLGP_DIRLIGHT_H
