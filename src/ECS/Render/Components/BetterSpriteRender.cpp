//
// Created by redkc on 15/06/2024.
//

#include "ECS/Entity.h"
#include "BetterSpriteRender.h"

bool BetterSpriteRender::draw(Shader &regularShader, Frustum *frustum) {
    ZoneScopedN("Draw");
    if(aabb.isOnFrustum(*frustum,getEntity()->transform)) {
        regularShader.use();
        regularShader.setFloat("alpha", alpha);
        texture->use(GL_TEXTURE0);
        regularShader.setInt("diffuseTexture", 0);
        regularShader.setFloat("depthBias", depthBias);
        regularShader.setFloat("scale", scale);
        regularShader.setBool("isBilborded", isBilborded);
        regularShader.setMatrix4("model", false, glm::value_ptr(getEntity()->transform.getModelMatrix()));
        return true;
    }
    return false;
}

void BetterSpriteRender::showImGuiDetailsImpl(Camera *camera) {
    Component::showImGuiDetailsImpl(camera);
}

BetterSpriteRender::BetterSpriteRender(Texture *texture, float timer): texture(texture) {
    name = "BetterSpriteRender";
    if(timer == 0.0f){
        isConstant = true;
    }
}

void BetterSpriteRender::UpdateImpl() {
    if (!isConstant) {
        timer = timer - (float) Time::Instance().DeltaTime();
        if (timer <= 0) {
            parentEntity->getComponent<BetterSpriteRender>()->Remove();
        }
    }
}
