//
// Created by redkc on 16/01/2024.
//

#include "ECS/Entity.h"
#include "SpotLight.h"

void SpotLight::Innit(int width, int height, int index) {
    glGenFramebuffers(1, &depthMapFBO);
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

void SpotLight::SetUpShadowBuffer(Shader *shadowMapShader, Shader *instanceShadowMapShader, int width, int height,
                                  GLuint ShadowMapArrayId, int index) {

        shadowMapShader->use();
        shadowMapShader->setMatrix4("lightSpaceMatrix", false, glm::value_ptr(data.lightSpaceMatrix));   
        shadowMapShader->setFloat("near_plane",far_plane);    
        shadowMapShader->setFloat("far_plane",near_plane);
        instanceShadowMapShader->use();
        instanceShadowMapShader->setMatrix4("lightSpaceMatrix", false, glm::value_ptr(data.lightSpaceMatrix));
    instanceShadowMapShader->setFloat("near_plane",far_plane);
    instanceShadowMapShader->setFloat("far_plane",near_plane);
    
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

SpotLight::SpotLight(SpotLightData data) : data(data) {
    name = "Spot light";

    lightType = Spot;
}

void SpotLight::showImGuiDetails(Camera *camera) {
    ImGui::InputFloat4("Diffuse", glm::value_ptr(data.diffuse));
    ImGui::InputFloat4("Specular", glm::value_ptr(data.specular));
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

    far_plane = ComputeFarPlane(data.constant,data.linear,data.quadratic);
    
    this->setIsDirty(false);
}
