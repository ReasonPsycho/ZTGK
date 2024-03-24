//
// Created by redkc on 25/02/2024.
//

#include "ECS/Entity.h"
#include "Render.h"

Render::Render(Model *pModel):pModel(pModel) {

}

void Render::draw(Shader &regularShader) {
    regularShader.setMatrix4("model", false, glm::value_ptr(getEntity()->transform.getModelMatrix()));
    pModel->Draw(regularShader);
}

void Render::showImGuiDetails(Camera *camera) {
    ImGui::PushID(uniqueID);
    if (ImGui::TreeNode("Render")) {
        // Display other light properties...
        ImGui::TreePop();
    }
    ImGui::PopID();
}

void Render::simpleDraw(Shader &regularShader) {
    regularShader.setMatrix4("model", false, glm::value_ptr(getEntity()->transform.getModelMatrix()));
    pModel->SimpleDraw(regularShader);
}
