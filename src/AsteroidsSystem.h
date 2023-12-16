//
// Created by redkc on 14/12/2023.
//

#ifndef OPENGLGP_ASTEROIDSSYSTEM_H
#define OPENGLGP_ASTEROIDSSYSTEM_H

#include "glm/vec3.hpp"
#include "glm/trigonometric.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "modelLoading/Shader.h"
#include "modelLoading/ComputeShader.h"
#include "glm/gtc/random.hpp"
#include "modelLoading/Model.h"
#include <glbinding/gl/gl.h>

using namespace gl;

struct AsteroidData {
    glm::mat4 model;
    glm::vec4 velocity;
    glm::vec4 rotation;
};

static string asteroidModelPath = "C:/Users/redkc/CLionProjects/assignment-x-the-project-ReasonPsycho/res/models/asteroid/rock.obj";


class AsteroidsSystem {
public:
    GLuint ID{};
    AsteroidsSystem(int size);
    void Init();
    void Draw();
    std::vector<AsteroidData> asteroidsData;
    Model asteroidModel = Model(&asteroidModelPath);
    Shader asteroidShader = Shader("res/shaders/asteroid.vert", "res/shaders/asteroid.frag");
    ComputeShader computeShader = ComputeShader("res/shaders/asteroid.glsl");
private:
    int size;
};


#endif //OPENGLGP_ASTEROIDSSYSTEM_H
