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
    glm::vec4 diffuse;
    glm::vec4 specular;
    glm::vec4 color;
    glm::vec4 position; //far plane will now be stored as 4th value in pos
    glm::vec4 direction;
    glm::mat4x4 lightSpaceMatrix;

    DirLightData(glm::vec4 diffuse= glm::vec4(glm::vec3 (255.0f),1),
                 glm::vec4 specular= glm::vec4(glm::vec3 (0),1),
                 glm::vec4 position = glm::vec4(0.0f),
    glm::vec4 direction = glm::vec4(1.0f),
    glm::mat4x4 lightSpaceMatrix = glm::mat4x4(1.0f))
            : diffuse(diffuse),
              specular(specular),
              position(position),
              direction(direction),
              lightSpaceMatrix(lightSpaceMatrix) // set to identity matrix
    {}
};

class DirLight : public ILight {
public:
    DirLight( DirLightData data);
    
    DirLightData data;

    void showImGuiDetailsImpl(Camera *camera) override;

    
    void Innit(int width, int height, int index) override;

    void SetUpShadowBuffer(Shader *shadowMapShader, Shader *instanceShadowMapShader, int width, int height,
                           GLuint ShadowMapArrayId, int index) override; // Pure virtual function


    void UpdateData(int height, int width) override;
    
    
private:
    float near_plane = 0.1f, far_plane = 50.0f;
    
};

#endif //OPENGLGP_DIRLIGHT_H
