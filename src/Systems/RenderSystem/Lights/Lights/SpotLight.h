//
// Created by redkc on 16/01/2024.
//

#ifndef OPENGLGP_SPOTLIGHT_H
#define OPENGLGP_SPOTLIGHT_H


#include "glm/vec4.hpp"
#include "imgui.h"
#include "../ILight.h"
#include "../../../../cmake-build-debug/_deps/imguizmo-src/ImGuizmo.h"
#include "glm/gtx/quaternion.hpp"

struct SpotLightData {
    glm::vec4 position;
    glm::vec4 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
    float pointlessfloat;
    float pointlessfloat2;
    float pointlessfloat3;

    glm::vec4 color;
};

class SpotLight : public ILight {
public:
    SpotLight(SpotLightData data) : data(data) {
        model = glm::mat4x4(1);
        model = glm::translate(model,
                               glm::vec3(data.position.x, data.position.y, data.position.z)); // Rotation around x-axis
        model = glm::rotate(model, data.direction.x, glm::vec3(1.0f, 0.0f, 0.0f)); // Rotation around x-axis
        model = glm::rotate(model, data.direction.y, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotation around y-axis
        model = glm::rotate(model, data.direction.z, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotation around z-axis    

    }

    SpotLightData data;

    void showImGuiDetails(Camera *camera) override {
        ImGui::PushID(uniqueID);

        if (ImGui::TreeNode("Spot light")) {
            ImGui::InputFloat4("Color", glm::value_ptr(data.color));
            ImGui::InputFloat("Constant", &data.constant);
            ImGui::InputFloat("Linear", &data.linear);
            ImGui::InputFloat("Quadratic", &data.quadratic);
            EditLight(camera);
            ImGui::TreePop();
        }
        ImGui::PopID();

    }

    void EditLight(Camera *camera) override {
        static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::ROTATE);
        static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);
        if (ImGui::IsKeyPressed(90))
            mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
        if (ImGui::IsKeyPressed(69))
            mCurrentGizmoOperation = ImGuizmo::ROTATE;

        if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
            mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
        ImGui::SameLine();
        if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
            mCurrentGizmoOperation = ImGuizmo::ROTATE;

        ImGui::InputFloat3("Position", glm::value_ptr(data.position));
        ImGui::InputFloat3("Rotation", glm::value_ptr(data.direction));

        static bool useSnap(false);
        if (ImGui::IsKeyPressed(83))
            useSnap = !useSnap;

        ImGuiIO &io = ImGui::GetIO();
        ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
        ImGuizmo::Manipulate(glm::value_ptr(camera->GetViewMatrix()), glm::value_ptr(camera->GetProjectionMatrix()),
                             mCurrentGizmoOperation, mCurrentGizmoMode, glm::value_ptr(model),
                             nullptr, nullptr);
        // Extract the rotation as a quaternion
        glm::quat q = glm::toQuat(model);
        // Convert the quaternion to Euler angles
        glm::vec3 eulerAngles = glm::eulerAngles(q);
        data.direction = glm::vec4(eulerAngles, 1);
        data.position = glm::vec4(glm::vec3(model[3]), 1);
    }
};


#endif //OPENGLGP_SPOTLIGHT_H
