//
// Created by redkc on 25/02/2024.
//

#ifndef REASONABLEGL_RENDER_H
#define REASONABLEGL_RENDER_H

#include "ECS/Component.h"
#include "modelLoading/Model.h"
#include "modelLoading/Shader.h"

class Render : public Component {
public:
    explicit Render(Model *pModel);
    void draw(Shader &regularShader);
private:
    Model *pModel{};
};


#endif //REASONABLEGL_RENDER_H
