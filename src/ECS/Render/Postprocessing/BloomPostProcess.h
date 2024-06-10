// 
// Created by redkc on 29/01/2024. 
// 
 
#ifndef OPENGLGP_BLOOMSYSTEM_H 
#define OPENGLGP_BLOOMSYSTEM_H 
 
 
#include "ECS/Render/ModelLoading/Shader.h" 
 
class BloomPostProcess { 
public: 
    ~BloomPostProcess(); 
 
 
    void Init(int SCR_WIDTH, int SCR_HEIGHT); 
 
    void BindBuffer(); 
 
    void SetUpBuffers(int SCR_WIDTH, int SCR_HEIGHT); 
 
    void BlurBuffer(); 
 
    void Render(); 
 
    void showImguiOptions(); 
 
    Shader shaderBlur = Shader("res/shaders/BloomSystem/Shaders/blur.vert", 
                               "res/shaders/BloomSystem/Shaders/blur.frag"); 
    Shader shaderBloomFinal = Shader("res/shaders/BloomSystem/Shaders/bloom_final.vert", 
                                     "res/shaders/BloomSystem/Shaders/bloom_final.frag"); 
private: 
    void DeleteGPUData(); 
     
    bool initialized = false; 
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
