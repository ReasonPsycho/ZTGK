//
// Created by redkc on 15/06/2024.
//

#include "ECS/Entity.h"
#include "BetterSpriteRender.h"
#include "ECS/Utils/Globals.h"
#include "ECS/Render/RenderSystem.h"
#include "ECS/Utils/RNG.h"
#include "ECS/Utils/CooldownComponentXDD.h"

bool BetterSpriteRender::draw(Shader &regularShader, Frustum *frustum) {
    ZoneScopedN("Draw");
    if(aabb.isOnFrustum(*frustum,getEntity()->transform) && !isInFogOfWar) {
        regularShader.use();
        regularShader.setFloat("alpha", alpha);
        texture->use(GL_TEXTURE0);
        regularShader.setInt("diffuseTexture", 0);
        regularShader.setFloat("depthBias", depthBias);
        regularShader.setFloat("scale", scale);
        glm::mat4 localModel = getEntity()->transform.getModelMatrix();
        if(isBilborded) {
            glm::vec3 scale  = glm::vec3(glm::length(localModel[0]), glm::length(localModel[1]), glm::length(localModel[2])); // Preserve object's scale
            glm::vec3 billboard_position = glm::vec3(localModel[3]);

            glm::vec3 look = glm::normalize(ztgk::game::camera->Position - billboard_position);
            glm::vec3 right = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), look);
            glm::vec3 up = glm::cross(look, right);

            localModel = glm::mat4(
                    glm::vec4(right * scale.x, 0.0f),
                    glm::vec4(up * scale.y, 0.0f),
                    glm::vec4(look * scale.z, 0.0f),
                    glm::vec4(billboard_position, 1.0f)
            );
        }
        
        regularShader.setMatrix4("model", false, glm::value_ptr(localModel));
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
    this->timer = timer;
    this->originalTimer = timer;
    this->Xdirection = RNG::RandomBool() ? 1 : -1;
    this->Xspeed = RNG::RandomFloat(0.5f, 1.2f);
    this->Zdirection = RNG::RandomBool() ? 1 : -1;
    this->Zspeed = RNG::RandomFloat(0.5f, 1.2f);
}

void BetterSpriteRender::UpdateImpl() {
    if (!isConstant) {
        if(firstFrame){
            firstFrame = false;
            getEntity()->transform.setLocalPosition(glm::vec3(0,1,0));
        }
        timer = timer - (float) Time::Instance().DeltaTime();
        auto percentTimeSpent = (originalTimer - timer) / originalTimer;

        //when the timer is halfway through, the alpha should be 1, when it is 0, the alpha should be 0
        if(timer < originalTimer/2.0f){
            alpha = percentTimeSpent * 2;
        }

        auto trans = getEntity()->transform.getLocalPosition();
        getEntity()->transform.setLocalPosition(
                glm::vec3(
                          Xspeed * absMaxSwayDistance * sin(2* percentTimeSpent * 3.1415) * Xdirection,
                          trans.y + 0.05 * (1 + percentTimeSpent),
                          Zspeed * absMaxSwayDistance * sin(2* percentTimeSpent * 3.1415) * Zdirection
                          ));
        getEntity()->updateSelfAndChild();

        if (timer <= 0) {
            toBeDeleted = true;
            getEntity()->transform.setLocalPosition(glm::vec3(0,0,0));
            getEntity()->addComponent(std::make_unique<CooldownComponentXDD>(RNG::RandomFloat(1.f, 3.f)));
        }
    }
}
