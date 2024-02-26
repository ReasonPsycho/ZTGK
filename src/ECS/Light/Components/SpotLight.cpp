//
// Created by redkc on 16/01/2024.
//

#include "ECS/Entity.h"
#include "SpotLight.h"

void SpotLight::InnitShadow() {
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

    glm::mat4 lightProjection, lightView;
    float near_plane = 1.0f, far_plane = 50.0f;
    lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat) SHADOW_WIDTH / (GLfloat) SHADOW_HEIGHT,
                                       near_plane,
                                       far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
    //lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);


    glm::vec3 lightPos = glm::vec3(data.position.x, data.position.y, data.position.z);


    glm::vec3 eulerAngles = data.direction;
    glm::vec3 direction = glm::vec3(
            cos(eulerAngles.x) * cos(eulerAngles.y), // dx
            sin(eulerAngles.y), // dy
            sin(eulerAngles.x) * cos(eulerAngles.y) // dz
    );
    direction = glm::normalize(direction); // Normalize vector

    lightView = glm::lookAt(lightPos, lightPos + direction, glm::vec3(0.0, 1.0, 0.0));
// Take in mind that glm::lookAt requires a position where the camera is located, a target where it should look at
// and an up vector to decide where is your top. Most likely, that it should be glm::vec3(0.0f, 1.0f, 0.0f)
    data.lightSpaceMatrix = lightProjection * lightView;
    // render scene from light's point of view

    initializedShadow = true;
}

void SpotLight::SetUpShadowBuffer(ShaderType shaderType,Shader* shadowMapShader,Shader* instanceShadowMapShader) {

    if (shaderType == Normal) {
        shadowMapShader->use();
        shadowMapShader->setMatrix4("lightSpaceMatrix", false, glm::value_ptr(data.lightSpaceMatrix));
    } else {
        instanceShadowMapShader->use();
        instanceShadowMapShader->setMatrix4("lightSpaceMatrix", false, glm::value_ptr(data.lightSpaceMatrix));
    }
    
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMap);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
}

SpotLight::SpotLight(SpotLightData data) : data(data) {
    lightType = Spot;
}

void SpotLight::showImGuiDetails(Camera *camera) {
    ImGui::PushID(uniqueID);

    if (ImGui::TreeNode("Spot light")) {
        ImGui::InputFloat4("Color", glm::value_ptr(data.color));
        ImGui::InputFloat("Constant", &data.constant);
        ImGui::InputFloat("Linear", &data.linear);
        ImGui::InputFloat("Quadratic", &data.quadratic);
        ImGui::InputFloat("Cut off", &data.cutOff);
        ImGui::InputFloat("Outer cut Off", &data.outerCutOff);
        EditLight(camera);
        ImGui::TreePop();
    }
    ImGui::PopID();

}

void SpotLight::EditLight(Camera *camera) {
    getEntity()->transform.ManipulateModelMatrix(camera);

    // Extract the rotation as a quaternion
    glm::quat q = glm::toQuat( getEntity()->transform.getModelMatrix());
    // Convert the quaternion to Euler angles
    glm::vec3 eulerAngles = glm::eulerAngles(q);
    data.direction = glm::vec4(eulerAngles, 1);
    data.position = glm::vec4( getEntity()->transform.getGlobalPosition(), 1);
}

