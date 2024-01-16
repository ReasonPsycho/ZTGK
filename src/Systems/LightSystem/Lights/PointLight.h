//
// Created by redkc on 16/01/2024.
//

#ifndef OPENGLGP_POINTLIGHT_H
#define OPENGLGP_POINTLIGHT_H


#include "glm/vec4.hpp"
#include "Systems/LightSystem/ILight.h"
#include "imgui.h"

struct PointLightData {
    glm::vec4  position;

    float constant;
    float linear;
    float quadratic;
    float pointlessfloat;

    glm::vec4 color;
};

class PointLight : public ILight {
public:
    PointLight(PointLightData data) : data(data){}
    PointLightData data;
    void showImGuiDetails() override {
        ImGui::PushID(uniqueID);

        if (ImGui::TreeNode("Point light")) {
            ImGui::Text("Direction: %.1f, %.1f, %.1f", data.position.x, data.position.y, data.position.z);
            ImGui::Text("Color: %.1f, %.1f, %.1f, %.1f", data.color.x, data.color.y, data.color.z, data.color.w);
            ImGui::Text("Constant: %.1f, Linear: %.1f, Quadratic: %.1f", data.constant, data.linear, data.quadratic);
            ImGui::TreePop();
        }
        ImGui::PopID();

    }
};


#endif //OPENGLGP_POINTLIGHT_H
