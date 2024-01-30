//
// Created by redkc on 30/01/2024.
//

#ifndef OPENGLGP_SHADOW_H
#define OPENGLGP_SHADOW_H

#include <vector>
#include "glad/glad.h"
#include "glm/vec3.hpp"
#include "modelLoading/Shader.h"
#include "glm/fwd.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shadow {
public:
    Shadow(glm::vec3 lightPos, Shader *shader) : lightPos(lightPos), depthShader(shader) {};

    void Init();

    void Generate(void (*funcPtr)());

    ~Shadow();

    unsigned int depthCubemap;

    bool isPointLight;
private:
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMapFBO;

    float near_plane = 1.0f; //TODO add so it's actually matching how far light reaches
    float far_plane = 25.0f;

    glm::mat4 shadowProj;
    std::vector<glm::mat4> shadowTransforms;
    glm::vec3 lightPos;
    Shader *depthShader;
};


#endif //OPENGLGP_SHADOW_H
