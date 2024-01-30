//
// Created by redkc on 16/01/2024.
//

#ifndef OPENGLGP_POINTLIGHT_H
#define OPENGLGP_POINTLIGHT_H


#include "glm/vec4.hpp"
#include "imgui.h"
#include "ILight.h"

#include "../../../../cmake-build-debug/_deps/imguizmo-src/ImGuizmo.h"

struct PointLightData {
    glm::vec4 position;

    float constant;
    float linear;
    float quadratic;
    float pointlessfloat;

    glm::vec4 color;
};

class PointLight : public ILight {
public:
    PointLight(Shader *shadowMapShader, PointLightData data) : ILight(shadowMapShader), data(data) {
        lightType = Point;
        model = glm::mat4x4(1);
        model = glm::translate(model,
                               glm::vec3(data.position.x, data.position.y, data.position.z)); // Rotation around x-axis
    }


    PointLightData data;

    void showImGuiDetails(Camera *camera) override {
        ImGui::PushID(uniqueID);

        if (ImGui::TreeNode("Point light")) {
            ImGui::InputFloat4("Color", glm::value_ptr(data.color));
            ImGui::InputFloat("Constant", &data.constant);
            ImGui::InputFloat("Linear", &data.linear);
            ImGui::InputFloat("Quadratic", &data.quadratic);
            EditLight(camera);
            // Display other light properties...
            ImGui::TreePop();
        }
        ImGui::PopID();

    }

    void EditLight(Camera *camera) override {
        static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
        static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);

        ImGui::InputFloat4("Position", glm::value_ptr(data.position));
        ImGuiIO &io = ImGui::GetIO();
        ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
        ImGuizmo::Manipulate(glm::value_ptr(camera->GetViewMatrix()), glm::value_ptr(camera->GetProjectionMatrix()),
                             mCurrentGizmoOperation, mCurrentGizmoMode, glm::value_ptr(model),
                             nullptr, nullptr);
        data.position = glm::vec4(glm::vec3(model[3]), 1);
    }

    void InnitShadow() override;

    void GenerateShadow(void (*funcPtr)()) override; // Pure virtual function

private:
    std::vector<glm::mat4> shadowTransforms;
};


#endif //OPENGLGP_POINTLIGHT_H
