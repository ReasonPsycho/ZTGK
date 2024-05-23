//
// Created by redkc on 15/04/2024.
//

#ifndef ZTGK_PHONGPIPELINE_H
#define ZTGK_PHONGPIPELINE_H


#include "ECS/Render/ModelLoading/Shader.h"
#include "ECS/Render/Camera/Camera.h"
#include "ECS/Render/RenderSystem.h"
#include "ECS/Render/Primitives/Primitives.h"

class PhongPipeline { //Renemane it to toonpipline XDD

public:
    void Init(Camera *camera,Primitives* primitives);
    void PrebindPipeline(Camera *camera);
    void WriteToBackBuffer(Camera *camera);

    void SetUpTextureBuffers(int width, int height);
    Shader phongShader = Shader("res/shaders/phong.vert", "res/shaders/phong.frag");
    Shader phongInstanceShader = Shader("res/shaders/phongInstance.vert", "res/shaders/phongInstance.frag");
    Shader textureSampler = Shader("res/shaders/textureSampler.vert", "res/shaders/textureSampler.frag");
    
private:
    Primitives* _primitives;
    GLuint frameBuffer;
    GLuint colorAttachments[2];
    GLuint rbo;
    bool isInnit = false;
};


#endif //ZTGK_PHONGPIPELINE_H
