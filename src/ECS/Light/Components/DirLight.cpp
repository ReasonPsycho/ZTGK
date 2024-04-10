//
// Created by redkc on 16/01/2024.
//

#include "ECS/Entity.h"
#include "DirLight.h"

void DirLight::Innit(int width, int height, int index) {
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
    lightProjection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, near_plane, far_plane);

    float scale_factor = 25.0f;
// assume data.direction contains Euler angles (yaw, pitch, roll)
    glm::vec3 forward = glm::vec3(1,0,0);
    data.direction =  glm::vec4(glm::rotate(getEntity()->transform.getLocalRotation(), forward),1);
    glm::vec3 translatedPos = -scale_factor * data.direction; //adjust the sign and scale
    lightView = glm::lookAt(translatedPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    data.lightSpaceMatrix = lightProjection * lightView;
;
}

void
DirLight::SetUpShadowBuffer(ShaderType shaderType, Shader *shadowMapShader, Shader *instanceShadowMapShader, int width,
                            int height, GLuint ShadowMapArrayId, int index) {
    if (shaderType == Normal) {
        shadowMapShader->use();
        shadowMapShader->setMatrix4("lightSpaceMatrix", false, glm::value_ptr(data.lightSpaceMatrix));
    } else {
        instanceShadowMapShader->use();
        instanceShadowMapShader->setMatrix4("lightSpaceMatrix", false, glm::value_ptr(data.lightSpaceMatrix));
      
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, index);
    glClear(GL_DEPTH_BUFFER_BIT);    
    glViewport(0, 0, width, height);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        spdlog::error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
}

DirLight::DirLight(DirLightData data) :
        data(data) {
    name = "Directional light";
    lightType = Directional;
}

void DirLight::showImGuiDetails(Camera *camera) {
        ImGui::InputFloat4("Color", glm::value_ptr(data.color));
        ImGui::TreePop();
}

void DirLight::UpdateData(int height, int width) {

    glm::mat4 lightProjection, lightView;
    lightProjection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, near_plane, far_plane);

    float scale_factor = 25.0f;
// assume data.direction contains Euler angles (yaw, pitch, roll)
    glm::vec3 forward = glm::vec3(1,0,0);
    data.direction =  glm::vec4(glm::rotate(getEntity()->transform.getLocalRotation(), forward),1);
    glm::vec3 translatedPos = -scale_factor * data.direction; //adjust the sign and scale
    lightView = glm::lookAt(translatedPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    data.lightSpaceMatrix = lightProjection * lightView;
    this->setIsDirty(false); //Just assume is dirty even when I just show it. Lol
}

