//
// Created by redkc on 15/04/2024.
//

#ifndef ZTGK_PHONGPIPELINE_H
#define ZTGK_PHONGPIPELINE_H


#include "ECS/Render/ModelLoading/Shader.h"
#include "ECS/Render/Camera/Camera.h"

class PhongPipeline {

public:
    void Init();
    void PrebindPipeline(Camera *camera);
    Shader phongShader = Shader("res/shaders/phong.vert", "res/shaders/phong.frag");
    Shader phongInstanceShader = Shader("res/shaders/phongInstance.vert", "res/shaders/phong.frag");
};


#endif //ZTGK_PHONGPIPELINE_H
