//
// Created by redkc on 15/06/2024.
//

#ifndef ZTGK_REALSPRITERENDER_H
#define ZTGK_REALSPRITERENDER_H


#include "ECS/Render/Camera/Camera.h"
#include "ECS/Component.h"
#include "ECS/Render/FrustumCulling/Frustum.h"
#include "ECS/Utils/Time.h"

class BetterSpriteRender : public Component{
public:
    BetterSpriteRender(Texture *texture, float timer = 0.0f);
    bool draw(Shader &regularShader, Frustum * frustum);
    void UpdateImpl() override;
    void showImGuiDetailsImpl(Camera *camera) override;
    
    Texture* texture;
    AABB aabb= AABB(glm::vec3(-0.1),glm::vec3(0.1));

    bool isConstant = false;
    bool isBilborded = true;
    float timer = 0.0f;
    float scale = 1.0f;
    float alpha = 1.0f;
    float depthBias = 1.0f;
};


#endif //ZTGK_REALSPRITERENDER_H
