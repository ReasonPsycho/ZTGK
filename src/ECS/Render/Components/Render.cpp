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