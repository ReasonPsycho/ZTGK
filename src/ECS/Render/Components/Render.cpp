//
// Created by redkc on 25/02/2024.
//

#include "ECS/Entity.h"
#include "Render.h"

Render::Render(Model *pModel):pModel(pModel),aabb(generateAABB(*pModel)) {
    colorMask = glm::vec4(0);
    name = "Renderer";
}

void Render::draw(Shader &regularShader) {
    ZoneScopedN("Draw");
    isRendered = true;
    regularShader.use();
    regularShader.setMatrix4("model", false, glm::value_ptr(getEntity()->transform.getModelMatrix()));
    regularShader.setFloat("heightScale", 1.0);
    regularShader.setVec4("colorMask", colorMask);
    regularShader.setFloat("dirtLevel", dirtLevel);
    regularShader.setFloat("saturation", 3.0);
    regularShader.setBool("useNormalMap", false);
    regularShader.setBool("isInFogOfWar", isInFogOfWar);
    regularShader.setBool("isAnimated", isAnimated);
    if(isAnimated){
        for (int i = 0; i < animationTransforms.size(); ++i)
            regularShader.setMatrix4("finalBonesMatrices[" + std::to_string(i) + "]", false, glm::value_ptr(animationTransforms[i]));
    }
    pModel->Draw(regularShader);
}

void Render::draw(Shader &regularShader, Frustum *frustum) {
    ZoneScopedN("Draw");
    if(aabb.isOnFrustum(*frustum,getEntity()->transform)){
        isRendered = true;
        regularShader.setMatrix4("model", false, glm::value_ptr(getEntity()->transform.getModelMatrix()));
        regularShader.setVec4("colorMask", colorMask);
        regularShader.setFloat("dirtLevel", dirtLevel);
        regularShader.setBool("isInFogOfWar", isInFogOfWar);
        regularShader.setBool("isAnimated", isAnimated);
        if(isAnimated){
            for (int i = 0; i < animationTransforms.size(); ++i)
                regularShader.setMatrix4("finalBonesMatrices[" + std::to_string(i) + "]", false, glm::value_ptr(animationTransforms[i]));
        }

        pModel->Draw(regularShader);    
    }else{
        isRendered = false;
    }
}

void Render::showImGuiDetailsImpl(Camera *camera) {
    ImGui::InputFloat("Dirt level",&dirtLevel);
    ImGui::Checkbox("Is in fog of war",&isInFogOfWar);
}

void Render::simpleDraw(Shader &regularShader) {
    ZoneScopedN("Simple draw");
    regularShader.setMatrix4("model", false, glm::value_ptr(getEntity()->transform.getModelMatrix()));
    pModel->SimpleDraw(regularShader);
}


