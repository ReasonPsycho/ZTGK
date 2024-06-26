//
// Created by redkc on 16/01/2024.
//

#include "ECS/Entity.h"
#include "PointLight.h"

void PointLight::Innit(int width, int height, int index) {
    shadowProj = glm::perspective(glm::radians(90.0f), (float) width / (float) height,
                                  near_plane, far_plane); //TODO add based pn calculation
    shadowTransforms.push_back(
            shadowProj *
            glm::lookAt(glm::vec3(data.position), glm::vec3(data.position) + glm::vec3(1.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(
            shadowProj *
            glm::lookAt(glm::vec3(data.position), glm::vec3(data.position) + glm::vec3(-1.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(
            shadowProj *
            glm::lookAt(glm::vec3(data.position), glm::vec3(data.position) + glm::vec3(0.0f, 1.0f, 0.0f),
                        glm::vec3(0.0f, 0.0f, 1.0f)));
    shadowTransforms.push_back(
            shadowProj *
            glm::lookAt(glm::vec3(data.position), glm::vec3(data.position) + glm::vec3(0.0f, -1.0f, 0.0f),
                        glm::vec3(0.0f, 0.0f, -1.0f)));
    shadowTransforms.push_back(
            shadowProj *
            glm::lookAt(glm::vec3(data.position), glm::vec3(data.position) + glm::vec3(0.0f, 0.0f, 1.0f),
                        glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(
            shadowProj *
            glm::lookAt(glm::vec3(data.position), glm::vec3(data.position) + glm::vec3(0.0f, 0.0f, -1.0f),
                        glm::vec3(0.0f, -1.0f, 0.0f)));

}

void PointLight::SetUpShadowBuffer(Shader *shadowMapShader, GLuint ShadowMapArrayId, int index, int layer) {
    ZoneScopedN("SetUpShadowBuffer");

        shadowMapShader->use();
        shadowMapShader->setMatrix4("shadowMatrice", false,
                                    glm::value_ptr(shadowTransforms[layer]));
        shadowMapShader->setFloat("far_plane", far_plane);
        shadowMapShader->setFloat("near_plane", near_plane);
        shadowMapShader->setVec3("lightPos", data.position.x, data.position.y, data.position.z);
    
        
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, ShadowMapArrayId, 0, layer + index * 6);
    glClear(GL_DEPTH_BUFFER_BIT);
}

PointLight::PointLight(PointLightData data) :
        data(data) {
    name = "Point light";

    lightType = Point;
}

void PointLight::showImGuiDetailsImpl(Camera *camera) {

    ImGui::ColorEdit4("Diffuse", glm::value_ptr(data.diffuse));
    ImGui::ColorEdit4("Specular", glm::value_ptr(data.specular));
    ImGui::InputFloat("Constant", &data.constant);
    ImGui::InputFloat("Linear", &data.linear);
    ImGui::InputFloat("Quadratic", &data.quadratic);
    if(ImGui::Button("Update")){
        this->setIsDirty(true);
    }
}

void PointLight::UpdateData(int height, int width) {
    ZoneScopedN("UpdateData");

    shadowTransforms.clear();
    this->getEntity()->forceUpdateSelfAndChild();
    data.position = glm::vec4(this->getEntity()->transform.getGlobalPosition(), far_plane);
    shadowProj = glm::perspective(glm::radians(90.0f), (float) width / (float) height,
                                  1.0f, far_plane);
    shadowTransforms.push_back(
            shadowProj *
            glm::lookAt(glm::vec3(data.position), glm::vec3(data.position) + glm::vec3(1.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(
            shadowProj *
            glm::lookAt(glm::vec3(data.position), glm::vec3(data.position) + glm::vec3(-1.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(
            shadowProj *
            glm::lookAt(glm::vec3(data.position), glm::vec3(data.position) + glm::vec3(0.0f, 1.0f, 0.0f),
                        glm::vec3(0.0f, 0.0f, 1.0f)));
    shadowTransforms.push_back(
            shadowProj *
            glm::lookAt(glm::vec3(data.position), glm::vec3(data.position) + glm::vec3(0.0f, -1.0f, 0.0f),
                        glm::vec3(0.0f, 0.0f, -1.0f)));
    shadowTransforms.push_back(
            shadowProj *
            glm::lookAt(glm::vec3(data.position), glm::vec3(data.position) + glm::vec3(0.0f, 0.0f, 1.0f),
                        glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(
            shadowProj *
            glm::lookAt(glm::vec3(data.position), glm::vec3(data.position) + glm::vec3(0.0f, 0.0f, -1.0f),
                        glm::vec3(0.0f, -1.0f, 0.0f)));

    this->setIsDirty(false); //Just assume is dirty even when I just show it. Lol
}

PointLight::PointLight(): data(PointLightData()) {
    name = "Point light";

    lightType = Point;
}
