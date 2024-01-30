//
// Created by redkc on 16/01/2024.
//

#include "DirLight.h"

void DirLight::InnitShadow() {
    if (initializedShadow) {
        DeleteShadow();
    }
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
                 NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = {1.0, 1.0, 1.0, 1.0};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    initializedShadow = true;
}

void DirLight::GenerateShadow(void (*funcPtr)()) {
    glm::mat4 lightProjection, lightView;
    float near_plane = 1.0f, far_plane = 100.0f;
    //lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat) SHADOW_WIDTH / (GLfloat) SHADOW_HEIGHT,
    // near_plane,
    //   far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
    lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    float scale_factor = 10.0f;
    glm::vec3 translatedPox = -scale_factor * glm::vec3(data.direction.x, data.direction.y, data.direction.z);
    lightView = glm::lookAt(translatedPox, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    data.position = glm::vec4(translatedPox, 1.0f);
    data.lightSpaceMatrix = lightProjection * lightView;
    // render scene from light's point of view
    shadowMapShader->use();
    shadowMapShader->setMatrix4("lightSpaceMatrix", false, glm::value_ptr(data.lightSpaceMatrix));

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthMap);
    funcPtr();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

