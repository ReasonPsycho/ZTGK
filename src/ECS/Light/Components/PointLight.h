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
    glm::vec4 diffuse;
    glm::vec4 specular;
    glm::vec4 position;
    float constant;
    float linear;
    float quadratic;
    float pointlessfloat;

    //Default constructor
    PointLightData(  glm::vec4 diffuse = glm::vec4(glm::vec3 (255.0f),1),
                     glm::vec4 specular= glm::vec4(glm::vec3 (0),1),
    glm::vec4 position = glm::vec4(0.0f),
    float constant = 1,
    float linear = 1,
    float quadratic = 1)
            : diffuse(diffuse),
              specular(specular),
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


    void showImGuiDetailsImpl(Camera *camera) override;
    
    void Innit(int width, int height, int index) override;

    void SetUpShadowBuffer(Shader *shadowMapShader, Shader *instanceShadowMapShader, int width, int height,
                           GLuint ShadowMapArrayId, int index) override; // Pure virtual function
    void UpdateData(int height, int width) override;

private:
    float near_plane = 0.1f, far_plane = 50.0f;
    std::vector<glm::mat4> shadowTransforms;
};


#endif //OPENGLGP_POINTLIGHT_H
