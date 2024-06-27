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

class PhongPipeline : public System { //Renemane it to toonpipline XDD

public:
    PhongPipeline();
    
    void Init(Camera *camera, Primitives *primitives);
    void PrebindPipeline(Camera *camera);
    void WriteToBackBuffer(Camera *camera);
    void SetUpTextureBuffers(int width, int height);
    void CalculateMipmapLevels(int width, int height);
    void PrepareFoamMap(Camera* camera);
    void CheckFramebuffer();

    float getGamma() const { return gamma; }
    void setGamma(float gamma) { this->gamma = gamma; }
    float getBloomIntensity() const { return m_bloom_intensity; }
    void setBloomIntensity(float bloomIntensity) { this->m_bloom_intensity = bloomIntensity; }

    //ECS
    void registerComponents() override{};
    void addComponent(void* component) override;
    void removeComponent(void* component) override;
    void showImGuiDetailsImpl(Camera *camera) override;
    void UpdateImpl() override;
    
    const std::type_index* getComponentTypes() override {return nullptr; };
    int getNumComponentTypes() override { return 0;};
    
    
    Shader phongShader = Shader("res/shaders/phong.vert", "res/shaders/phong.frag");
    Shader spriteRenderShader = Shader("res/shaders/spriteRender.vert", "res/shaders/spriteRender.frag");
    Shader phongInstanceShader = Shader("res/shaders/phongInstance.vert", "res/shaders/phongInstance.frag");
    Shader phongInstanceLightShader = Shader("res/shaders/emmisonInstance.vert", "res/shaders/emmisonInstance.frag");
    Shader textureSampler = Shader("res/shaders/textureSampler.vert", "res/shaders/textureSampler.frag");
    Shader stencilTest = Shader("res/shaders/fogOfWarMask.vert", "res/shaders/fogOfWarMask.frag");
    Shader foamMaskShader = Shader("res/shaders/foamShader.vert", "res/shaders/foamShader.frag");
    Shader particleShader = Shader("res/shaders/particle.vert", "res/shaders/particle.frag");
    Shader minimap = Shader("res/shaders/minimap.vert", "res/shaders/minimap.frag");
    ComputeShader particle = ComputeShader("res/shaders/particleMovment.comp");
    ComputeShader downscale = ComputeShader("res/shaders/downscale.comp");
    ComputeShader upscale = ComputeShader("res/shaders/upscale.comp");

    Texture *bloomDirtTexture;
    MaterialPhong foamMaterial;
    GLuint colorAttachments[4];
    Primitives *_primitives;
    
private:
    GLuint frameBuffer;
    GLuint rbo;
    bool toonTencilEnabled;
    bool isInnit = false;

    GLuint foamFrameBuffer;
    GLuint foamColorAttachment;


    //dirtMask 
    float dirtMultiplayer = 0.4;
    
    //gamma mapping
    float exposure = 1.0;
    float gamma = 1.5;

    //bloom
    bool bloomEnabled = true;
    float m_threshold = 1.5f;
    float m_knee = 0.1f;
    float m_bloom_intensity = 1.0f;
    float m_bloom_dirt_intensity = 0.0f;
    
    //toonshader
    float ambient = 0.3;
    float diffuse_levels = 3;
    float specular_levels = 3;
    float light_shade_cutoff = 0.8f;
    float dark_shade_cutoff = 0.5f;
    int toon_color_levels = 0.5f;
    
    float saturationMultiplayer = 0.5f;
    float lightMultiplayer = 0.5f;
    
    //rimlight
    float rim_threshold = 12;
    float rim_amount = 1.0f;
    float rim_multiplier = 0.2f;
    
    //outlines
    bool normalShaderOutlineMapping = true;
    bool lightShaderOutlineMapping = true;
    bool instanceShaderOutlineMapping = false;
    bool particleShaderOutlineMapping = false;
    float depth_threshold = 1;
    float depth_normal_threshold = 1;
    float depth_normal_threshold_scale = 0.2;
    float normal_threshold = 0.5;
    
    float outline_width = 1;
    glm::vec3 outline_color = glm::vec3(0);
    //bloom
    const uint8_t m_downscale_limit = 10;
    const uint8_t m_max_iterations = 16; // max mipmap levels
    uint8_t m_mip_levels = 1;

    //ECS
    std::array<std::type_index, 0> componentTypes = {};
};


#endif //ZTGK_PHONGPIPELINE_H
