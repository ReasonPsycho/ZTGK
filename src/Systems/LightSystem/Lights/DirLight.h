//
// Created by redkc on 16/01/2024.
//

#ifndef OPENGLGP_DIRLIGHT_H
#define OPENGLGP_DIRLIGHT_H


#include "glm/vec4.hpp"
#include "Systems/LightSystem/ILight.h"
#include "imgui.h"

struct DirLightData {
    glm::vec4 direction;
    glm::vec4 color;
};

class DirLight : public ILight {
public:
    DirLight(DirLightData data) : data(data) {}

    DirLightData data;

    void showImGuiDetails() override {
        ImGui::PushID(uniqueID);
        if (ImGui::TreeNode("Directional light")) {
            ImGui::Text("Direction: %.1f, %.1f, %.1f", data.direction.x, data.direction.y, data.direction.z);
            ImGui::Text("Color: %.1f, %.1f, %.1f, %.1f", data.color.x, data.color.y, data.color.z, data.color.w);
            // Display other light properties...
            ImGui::TreePop();
        }
        ImGui::PopID();
    }
};

#endif //OPENGLGP_DIRLIGHT_H
