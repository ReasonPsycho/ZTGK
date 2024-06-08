//
// Created by redkc on 25/02/2024.
//

#ifndef REASONABLEGL_RENDER_H
#define REASONABLEGL_RENDER_H

#include "ECS/Component.h"
#include "ECS/Render/ModelLoading/Model.h"
#include "ECS/Render/FrustumCulling/BoundingVolume.h"
#include <tracy/Tracy.hpp >


class Render : public Component {
public:
    Render(Model *pModel);
    void draw(Shader &regularShader);
    void draw(Shader &regularShader,Frustum * frustum);
    void simpleDraw(Shader &regularShader);
    void showImGuiDetailsImpl(Camera *camera) override;
    
    glm::vec4 colorMask;
    float dirtLevel;
private:
    Model *pModel{};
    AABB aabb;
};


#endif //REASONABLEGL_RENDER_H
