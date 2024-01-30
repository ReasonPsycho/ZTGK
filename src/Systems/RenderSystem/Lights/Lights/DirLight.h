//
// Created by redkc on 16/01/2024.
//

#ifndef OPENGLGP_DIRLIGHT_H
#define OPENGLGP_DIRLIGHT_H


#include "glm/vec4.hpp"
#include "imgui.h"
#include "../ILight.h"
#include "../../../../cmake-build-debug/_deps/imguizmo-src/ImGuizmo.h"
#include "glm/gtx/quaternion.hpp"

struct DirLightData {
    glm::vec4 direction;
    glm::vec4 color;
};

class DirLight : public ILight {
public:
    DirLight(DirLightData data) : data(data) {
        model = glm::mat4x4(1);
        model = glm::rotate(model, data.direction.x, glm::vec3(1.0f, 0.0f, 0.0f)); // Rotation around x-axis
        model = glm::rotate(model,  data.direction.y, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotation around y-axis
        model = glm::rotate(model,  data.direction.z, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotation around z-axis    
    }
    
    DirLightData data;

    void showImGuiDetails(Camera* camera) override {
        ImGui::PushID(uniqueID);
        if (ImGui::TreeNode("Directional light")) {
            ImGui::InputFloat4("Color",glm::value_ptr(data.color));
            EditLight(camera);
            // Display other light properties...
            ImGui::TreePop();
        }
        ImGui::PopID();
    }

    void EditLight(Camera* camera) override {
        static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::ROTATE);
        static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);
        
        ImGui::InputFloat3("Direction",glm::value_ptr(data.direction));
        
        ImGuiIO& io = ImGui::GetIO();
        ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
        ImGuizmo::Manipulate(glm::value_ptr(camera->GetViewMatrix()),glm::value_ptr( camera->GetProjectionMatrix()), mCurrentGizmoOperation, mCurrentGizmoMode, glm::value_ptr(model),
                             nullptr, nullptr);


// Extract the rotation as a quaternion
        glm::quat q = glm::toQuat(model);

// Convert the quaternion to Euler angles
        glm::vec3 eulerAngles = glm::eulerAngles(q);
        data.direction = glm::vec4(eulerAngles,1);
    }
    
};

#endif //OPENGLGP_DIRLIGHT_H
