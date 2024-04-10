//
// Created by redkc on 16/01/2024.
//

#include "ECS/Entity.h"
#include "PointLight.h"

void PointLight::Innit(int width, int height, int index) {
    glGenFramebuffers(1, &depthMapFBO);
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

    GLenum attachments[6];

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    for(int i = 0; i < 6; i++)
    {
        glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT + i, ShadowMapArrayId, 0, i * 6);
        attachments[i] = GL_DEPTH_ATTACHMENT + i;
    }

    glDrawBuffers(6, attachments);  
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
