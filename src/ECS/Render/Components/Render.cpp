//
// Created by redkc on 25/02/2024.
//

#include "ECS/Entity.h"
#include "Render.h"

Render::Render(Model *pModel):pModel(pModel),aabb(generateAABB(*pModel)) {
    name = "Renderer";
}

void Render::draw(Shader &regularShader) {
    ZoneScopedN("Draw");
    regularShader.setMatrix4("model", false, glm::value_ptr(getEntity()->transform.getModelMatrix()));
    regularShader.setFloat("heightScale", 1.0);
    regularShader.setBool("useNormalMap", false);
    pModel->Draw(regularShader);
}

void Render::draw(Shader &regularShader, Frustum *frustum) {
    ZoneScopedN("Draw");
    if(aabb.isOnFrustum(*frustum,getEntity()->transform)){
        regularShader.setMatrix4("model", false, glm::value_ptr(getEntity()->transform.getModelMatrix()));
        pModel->Draw(regularShader);    
    }
}

void Render::showImGuiDetailsImpl(Camera *camera) {
    
}

void Render::simpleDraw(Shader &regularShader) {
    ZoneScopedN("Simple draw");
    regularShader.setMatrix4("model", false, glm::value_ptr(getEntity()->transform.getModelMatrix()));
    pModel->SimpleDraw(regularShader);
}


