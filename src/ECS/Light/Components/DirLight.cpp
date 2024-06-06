//
// Created by redkc on 16/01/2024.
//

#include "ECS/Entity.h"
#include "DirLight.h"

void DirLight::Innit(int width, int height, int index) {
    glm::mat4 lightProjection, lightView;
    lightProjection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, near_plane, far_plane);

    float scale_factor = 25.0f;
// assume data.direction contains Euler angles (yaw, pitch, roll)
    glm::vec3 forward = glm::vec3(1, 0, 0);
    data.direction = glm::vec4(glm::rotate(getEntity()->transform.getLocalRotation(), forward), 1);
    glm::vec3 translatedPos = -scale_factor * data.direction; //adjust the sign and scale
    lightView = glm::lookAt(translatedPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    data.lightSpaceMatrix = lightProjection * lightView;;
}

void
DirLight::SetUpDepthShader(Shader *shadowMapShader, int layer) {
    ZoneScopedN("SetUpShadowBuffer");

    shadowMapShader->use();
    shadowMapShader->setMatrix4("lightSpaceMatrix", false, glm::value_ptr(data.lightSpaceMatrix));
    shadowMapShader->setFloat("far_plane", far_plane);
    shadowMapShader->setFloat("near_plane", near_plane);


}

DirLight::DirLight(DirLightData data) :
        data(data) {
    name = "Directional light";
    lightType = Directional;
}

void DirLight::showImGuiDetailsImpl(Camera *camera) {
    
    ImGui::ColorEdit4("Diffuse", glm::value_ptr(data.diffuse));
    ImGui::ColorEdit4("Specular", glm::value_ptr(data.specular));
    if(ImGui::Button("Update")){
        this->setIsDirty(true);
    }
}

void DirLight::UpdateData(int height, int width) {

    glm::mat4 lightProjection, lightView;
    lightProjection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, near_plane, far_plane);
    data.position[3] = far_plane;
    float scale_factor = 25.0f;
    // assume data.direction contains Euler angles (yaw, pitch, roll)
    glm::vec3 forward = glm::vec3(1, 0, 0);
    data.direction = glm::vec4(glm::rotate(getEntity()->transform.getLocalRotation(), forward), 1);
    glm::vec3 translatedPos = -scale_factor * data.direction; //adjust the sign and scale
    lightView = glm::lookAt(translatedPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    data.lightSpaceMatrix = lightProjection * lightView;
    this->setIsDirty(false); //Just assume is dirty even when I just show it. Lol
}

DirLight::DirLight():  ILight(),
        data(DirLightData())  {
    name = "Directional light";
    lightType = Directional;
}
