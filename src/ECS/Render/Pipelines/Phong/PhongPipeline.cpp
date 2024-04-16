//
// Created by redkc on 15/04/2024.
//

#include "PhongPipeline.h"

void PhongPipeline::Init() {

    phongShader.init();
}

void PhongPipeline::PrebindPipeline(Camera *camera) {
    glm::mat4 projection = camera->GetProjectionMatrix();
    glm::mat4 view = camera->GetViewMatrix();
    glm::vec3 cameraPos = camera->Position;

    phongShader.use();

    phongShader.setBool("shadows", true);
    phongShader.setMatrix4("projection", false, glm::value_ptr(projection));
    phongShader.setMatrix4("view", false, glm::value_ptr(view));
    phongShader.setVec3("camPos", cameraPos.x, cameraPos.y, cameraPos.z);
    phongShader.setFloat("far_plane", 25.0f);
}
