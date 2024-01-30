//
// Created by redkc on 29/01/2024.
//

#ifndef OPENGLGP_BLOOMSYSTEM_H
#define OPENGLGP_BLOOMSYSTEM_H


#include "modelLoading/Shader.h"
#include "Camera.h"

class BloomSystem {
    

 
public:
    void Init(float  SCR_WIDTH, float SCR_HEIGHT);
    void BindBuffer();
    void SetUpBuffers(float  SCR_WIDTH, float SCR_HEIGHT);
    void BlurBuffer();
    void Render();
    void showImguiOptions();

    Shader shaderBlur= Shader("res/shaders/BloomSystem/Shaders/blur.vert", "res/shaders/BloomSystem/Shaders/blur.frag");
    Shader shaderBloomFinal= Shader("res/shaders/BloomSystem/Shaders/bloom_final.vert", "res/shaders/BloomSystem/Shaders/bloom_final.frag");
private:
    unsigned int hdrFBO;
    unsigned int colorBuffers[2];
    unsigned int pingpongFBO[2];
    unsigned int pingpongColorbuffers[2];
    bool horizontal = true, first_iteration = true;
    unsigned int amount = 10;
    bool bloom = true;
    float exposure = 1.0f;
};


#endif //OPENGLGP_BLOOMSYSTEM_H
