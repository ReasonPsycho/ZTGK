//
// Created by redkc on 15/04/2024.
//

#ifndef ZTGK_PHONGPIPELINE_H
#define ZTGK_PHONGPIPELINE_H


#include "ECS/Render/ModelLoading/Shader.h"
#include "ECS/Render/Camera/Camera.h"
#include "ECS/Render/RenderSystem.h"
#include "ECS/Render/Primitives/Primitives.h"
#include "ECS/Render/ModelLoading/ComputeShader.h"
#include "ECS/Utils/Globals.h"

class PhongPipeline { //Renemane it to toonpipline XDD

public:
    void Init(Camera *camera, Primitives *primitives);

    void PrebindPipeline(Camera *camera);

    void WriteToBackBuffer(Camera *camera);

    void SetUpTextureBuffers(int width, int height);

    void CalculateMipmapLevels(int width, int height);
    
    void PrepareFoamMap(Camera* camera);

    Shader phongShader = Shader("res/shaders/phong.vert", "res/shaders/phong.frag");
    Shader phongInstanceShader = Shader("res/shaders/phongInstance.vert", "res/shaders/phongInstance.frag");
    Shader phongInstanceLightShader = Shader("res/shaders/emmisonInstance.vert", "res/shaders/emmisonInstance.frag");
    Shader textureSampler = Shader("res/shaders/textureSampler.vert", "res/shaders/textureSampler.frag");
    Shader stencilTest = Shader("res/shaders/fogOfWarMask.vert", "res/shaders/fogOfWarMask.frag");
    Shader foamMaskShader = Shader("res/shaders/foamShader.vert", "res/shaders/foamShader.frag");
    ComputeShader downscale = ComputeShader("res/shaders/downscale.comp");
    ComputeShader upscale = ComputeShader("res/shaders/upscale.comp");

    Texture *bloomDirtTexture;
    MaterialPhong *foamMaterial;
private:
    Primitives *_primitives;
    GLuint frameBuffer;
    GLuint colorAttachments[4];
    GLuint rbo;
    bool bloomEnabled = true;
    bool toonTencilEnabled;
    bool isInnit = false;

    GLuint foamFrameBuffer;
    GLuint foamColorAttachment;
    
    float exposure = 1;
    float gamma = 1.5;

    float m_threshold = 1.5f;
    float m_knee = 0.1f;
    float m_bloom_intensity = 1.0f;
    float m_bloom_dirt_intensity = 0.0f;

    const uint8_t m_downscale_limit = 10;
    const uint8_t m_max_iterations = 16; // max mipmap levels
    uint8_t m_mip_levels = 1;

    float diffuse_levels = 3;
    float specular_levels = 3;
    float light_shade_cutoff = 0.8f;
    float dark_shade_cutoff = 0.5f;

    float rim_threshold = 10;
    float rim_amount = 0.5f;
};


#endif //ZTGK_PHONGPIPELINE_H
