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
#include "LightHelpers.h"

struct SpotLightData {
    glm::vec4 diffuse;
    glm::vec4 specular;
    glm::vec4 position;//4th data in diffuse stores active bool
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

    SpotLightData( glm::vec4 diffuse = glm::vec4(glm::vec3 (5.0f),1),
                   glm::vec4 specular= glm::vec4(glm::vec3 (5),1),
    glm::vec4 position = glm::vec4(0.0f),
    glm::vec4 direction= glm::vec4(1.0f),
    float cutOff = 0.9763f,
    float outerCutOff = 0.96593f,
    float constant = 1.0f,
    float linear = 0.09f,
    float quadratic =  0.032f,
    glm::mat4x4 lightSpaceMatrix = glm::mat4x4(1.0f)
    )
            : diffuse(diffuse),
             specular(specular),
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
    float near_plane = 0.1f, far_plane = 1.0f;

public:
    SpotLight(SpotLightData data);
    SpotLight();



    SpotLightData data;

    void showImGuiDetailsImpl(Camera *camera) override;
    
    void Innit(int width, int height, int index) override;

    void SetUpDepthShader(Shader *shadowMapShader, int layer) override; // Pure virtual function
    void UpdateData(int height, int width) override;

};


#endif //OPENGLGP_SPOTLIGHT_H
