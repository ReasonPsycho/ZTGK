//
// Created by redkc on 10/01/2024.
//

#ifndef OPENGLGP_PBRSYSTEM_H
#define OPENGLGP_PBRSYSTEM_H

#include "ECS/Render/Primitives/Primitives.h"
#include <string>
#include "stb_image.h"
#include "glm/fwd.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/trigonometric.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ECS/Render/Camera/Camera.h"

class PBRPipeline {
public:
    PBRPipeline(Camera *camera,Primitives* primitives);

    void Init();

    void RenderBackground();

    void PrebindPBR(Camera *camera);

    Shader pbrInstanceShader = Shader("res/shaders/pbrBloomInstance.vert", "res/shaders/pbrBloomInstance.frag");
    Shader pbrShader = Shader("res/shaders/pbr.vert", "res/shaders/pbrBloomInstance.frag");
    Shader equirectangularToCubemapShader = Shader("res/shaders/cubemap.vert",
                                                   "res/shaders/equirectangular_to_cubemap.frag");
    Shader irradianceShader = Shader("res/shaders/cubemap.vert", "res/shaders/irradiance_convolution.frag");
    Shader prefilterShader = Shader("res/shaders/cubemap.vert", "res/shaders/prefilter.frag");
    Shader brdfShader = Shader("res/shaders/brdf.vert", "res/shaders/brdf.frag");
    Shader backgroundShader = Shader("res/shaders/background.vert", "res/shaders/background.frag");

private:
    unsigned int captureFBO;
    unsigned int captureRBO;
    
    Primitives*  primitives;
    Camera *camera;
    unsigned int envCubemap;
    unsigned int irradianceMap;
    unsigned int prefilterMap;
    unsigned int brdfLUTTexture;
    unsigned int hdrTexture;

};


#endif //OPENGLGP_PBRSYSTEM_H
