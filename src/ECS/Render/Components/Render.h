//
// Created by redkc on 25/02/2024.
//

#ifndef REASONABLEGL_RENDER_H
#define REASONABLEGL_RENDER_H

#include "ECS/Component.h"
#include "ECS/Render/ModelLoading/Model.h"

class Render : public Component {
public:
    explicit Render(Model *pModel);
    void draw(Shader &regularShader);
    void simpleDraw(Shader &regularShader);
    void showImGuiDetails(Camera *camera) override;

private:
    Model *pModel{};
};


#endif //REASONABLEGL_RENDER_H
