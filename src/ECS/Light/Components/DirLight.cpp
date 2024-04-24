//
// Created by redkc on 16/01/2024.
//

#include "ECS/Entity.h"
#include "DirLight.h"

void DirLight::Innit(int width, int height, int index) {
    glGenFramebuffers(1, &depthMapFBO);
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
DirLight::SetUpShadowBuffer(Shader *shadowMapShader, Shader *instanceShadowMapShader, int width, int height,
                            GLuint ShadowMapArrayId, int index) {
        shadowMapShader->use();
        shadowMapShader->setMatrix4("lightSpaceMatrix", false, glm::value_ptr(data.lightSpaceMatrix));
        instanceShadowMapShader->use();
        instanceShadowMapShader->setMatrix4("lightSpaceMatrix", false, glm::value_ptr(data.lightSpaceMatrix));

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, ShadowMapArrayId, 0, index);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);



    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        const char *errorType = "";
        switch (status) {
            case GL_FRAMEBUFFER_UNDEFINED:
                errorType = "GL_FRAMEBUFFER_UNDEFINED";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                errorType = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                errorType = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                errorType = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                errorType = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
                break;
            case GL_FRAMEBUFFER_UNSUPPORTED:
                errorType = "GL_FRAMEBUFFER_UNSUPPORTED";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
                errorType = "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
                errorType = "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
                break;
            default:
                errorType = "UNKNOWN_ERROR";
                break;
        }
        spdlog::error("ERROR::FRAMEBUFFER:: Framebuffer is not complete! Error: {}", errorType);
    }
}

DirLight::DirLight(DirLightData data) :
        data(data) {
    name = "Directional light";
    lightType = Directional;
}

void DirLight::showImGuiDetails(Camera *camera) {
        ImGui::InputFloat4("Diffuse", glm::value_ptr(data.diffuse));
        ImGui::InputFloat4("Specular", glm::value_ptr(data.specular));
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

