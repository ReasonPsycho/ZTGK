//
// Created by redkc on 16/01/2024.
//

#include "ECS/Entity.h"
#include "SpotLight.h"

void SpotLight::Innit(int width, int height, int index) {
    if (initializedShadow) {
        DeleteShadow();
    }
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
                 NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = {1.0, 1.0, 1.0, 1.0};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, index);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glm::mat4 lightProjection, lightView;
    lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat) width / (GLfloat) height,
                                       near_plane,
                                       far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
    //lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);


    glm::vec3 lightPos = glm::vec3(data.position.x, data.position.y, data.position.z);


    glm::vec3 eulerAngles = data.direction;
    glm::vec3 direction = glm::vec3(0, 0, 0);
    direction = glm::normalize(direction); // Normalize vector

    lightView = glm::lookAt(lightPos, lightPos + direction, glm::vec3(0.0, 1.0,
                                                                      0.0)); //TODO when shadows gonna be here change that to appropriate things
// Take in mind that glm::lookAt requires a position where the camera is located, a target where it should look at
// and an up vector to decide where is your top. Most likely, that it should be glm::vec3(0.0f, 1.0f, 0.0f)
    data.lightSpaceMatrix = lightProjection * lightView;
    // render scene from light's point of view
}

void SpotLight::SetUpShadowBuffer(ShaderType shaderType, Shader *shadowMapShader, Shader *instanceShadowMapShader, int width,
                                  int height, GLuint ShadowMapArrayId, int index) {

    if (shaderType == Normal) {
        shadowMapShader->use();
        shadowMapShader->setMatrix4("lightSpaceMatrix", false, glm::value_ptr(data.lightSpaceMatrix));
    } else {
        instanceShadowMapShader->use();
        instanceShadowMapShader->setMatrix4("lightSpaceMatrix", false, glm::value_ptr(data.lightSpaceMatrix));

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

SpotLight::SpotLight(SpotLightData data) : data(data) {
    name = "Spot light";

    lightType = Spot;
}

void SpotLight::showImGuiDetails(Camera *camera) {
        ImGui::InputFloat4("Color", glm::value_ptr(data.color));
        ImGui::InputFloat("Constant", &data.constant);
        ImGui::InputFloat("Linear", &data.linear);
        ImGui::InputFloat("Quadratic", &data.quadratic);
        ImGui::InputFloat("Cut off", &data.cutOff);
        ImGui::InputFloat("Outer cut Off", &data.outerCutOff);
}

void SpotLight::UpdateData(int height, int width) {
    glm::mat4 lightProjection, lightView;
    lightProjection = glm::perspective(data.outerCutOff, (GLfloat) width / (GLfloat) height, near_plane, far_plane);

    glm::vec3 forward = glm::vec3(1,0,0);
    glm::quat globalRotation = getEntity()->transform.getGlobalRotation();

    data.position = glm::vec4(getEntity()->transform.getGlobalPosition(), 1.0f);
    glm::vec3 direction = glm::rotate(globalRotation, forward);
    data.direction = glm::vec4(direction, 0.0f);

    glm::vec3 lightPos = glm::vec3(data.position);
    glm::vec3 target = lightPos + direction;

    // To define the 'up' direction for lookAt function 
    // you will generally use glm::vec3(0.0f, 1.0f, 0.0f) if your world's 'up' vector is along y-axis
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    lightView = glm::lookAt(lightPos, target, up);

    data.lightSpaceMatrix = lightProjection * lightView;

    this->setIsDirty(false);
}
