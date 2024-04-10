//
// Created by redkc on 16/01/2024.
//

#include "ECS/Entity.h"
#include "PointLight.h"

void PointLight::Innit(int width, int height, int index) {
    if (initializedShadow) {
        DeleteShadow();
    }
    glGenFramebuffers(1, &depthMapFBO);
    // create depth cubemap texture
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthMap);
    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, height, index, 0,
                     GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, index);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

void PointLight::SetUpShadowBuffer(ShaderType shaderType, Shader *shadowMapShader, Shader *instanceShadowMapShader, int width,
                                   int height, GLuint ShadowMapArrayId, int index) {

    shadowMapShader->use();
    for (unsigned int i = 0; i < 6; ++i)
        if (shaderType == Normal) {
            shadowMapShader->setMatrix4("shadowMatrices[" + std::to_string(i) + "]", false,
                                        glm::value_ptr(shadowTransforms[i]));
            shadowMapShader->setFloat("far_plane", far_plane);
            shadowMapShader->setVec3("lightPos", data.position.x, data.position.y, data.position.z);
        } else {
            shadowMapShader->setMatrix4("shadowMatrices[" + std::to_string(i) + "]", false,
                                        glm::value_ptr(shadowTransforms[i]));
            instanceShadowMapShader->setFloat("far_plane", near_plane);
            instanceShadowMapShader->setVec3("lightPos", data.position.x, data.position.y, data.position.z);
        }

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, ShadowMapArrayId, 0, index);
    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMap);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        spdlog::error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
}

PointLight::PointLight(PointLightData data):
                                                                    data(data) {
    name = "Point light";

    lightType = Point;
}

void PointLight::showImGuiDetails(Camera *camera) {
  
        ImGui::InputFloat4("Color", glm::value_ptr(data.color));
        ImGui::InputFloat("Constant", &data.constant);
        ImGui::InputFloat("Linear", &data.linear);
        ImGui::InputFloat("Quadratic", &data.quadratic);

}

void PointLight::UpdateData(int height, int width) {
    shadowTransforms.clear();
    shadowProj = glm::perspective(glm::radians(90.0f), (float) width / (float) height,
                                  1.0f, 25.0f); //TODO add based pn calculation
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

    data.position = glm::vec4(this->getEntity()->transform.getGlobalPosition(),0);
    this->setIsDirty(false); //Just assume is dirty even when I just show it. Lol
}
