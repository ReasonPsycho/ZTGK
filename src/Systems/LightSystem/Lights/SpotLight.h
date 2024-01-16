//
// Created by redkc on 16/01/2024.
//

#ifndef OPENGLGP_SPOTLIGHT_H
#define OPENGLGP_SPOTLIGHT_H


#include "glm/vec4.hpp"
#include "Systems/LightSystem/ILight.h"
#include "imgui.h"

struct SpotLightData {
    glm::vec4  position;
    glm::vec4  direction;
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
    SpotLight(SpotLightData data) : data(data){}
    SpotLightData data;
    void showImGuiDetails() override {
        ImGui::PushID(uniqueID);

        if (ImGui::TreeNode("Spot light")) {
            ImGui::Text("Direction: %.1f, %.1f, %.1f", data.position.x, data.position.y, data.position.z);
            ImGui::Text("Color: %.1f, %.1f, %.1f, %.1f", data.color.x, data.color.y, data.color.z, data.color.w);
            ImGui::Text("Constant: %.1f, Linear: %.1f, Quadratic: %.1f", data.constant, data.linear, data.quadratic);
            ImGui::Text("CutOff: %.1f, OuterCutOff: %.1f", data.cutOff, data.outerCutOff);
            ImGui::TreePop();
        }
        ImGui::PopID();

    }
};


#endif //OPENGLGP_SPOTLIGHT_H
