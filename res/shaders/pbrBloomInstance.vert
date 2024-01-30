#version 460
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;

struct AsteroidData
{
    vec4 position;
    vec4 rotation;
    vec4 scale;
    vec4 velocity;
    vec4 angularVelocity;
    vec4 separationVector;
};


layout (std430, binding = 0) buffer AsteroidBuffer {
    AsteroidData asteroidsData[]; // Array of velocities
};


uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

mat4 translateMatrix(vec3 translation) {
    return mat4(
        vec4(1.0, 0.0, 0.0, 0.0),
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(0.0, 0.0, 1.0, 0.0),
        vec4(translation, 1.0)
    );
}

mat4 rotateX(float theta) {
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);
    return mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, cosTheta, -sinTheta, 0.0,
        0.0, sinTheta, cosTheta, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

mat4 rotateY(float theta) {
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);
    return mat4(
        cosTheta, 0.0, sinTheta, 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sinTheta, 0.0, cosTheta, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

mat4 rotateZ(float theta) {
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);
    return mat4(
        cosTheta, -sinTheta, 0.0, 0.0,
        sinTheta, cosTheta, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

mat4 rotateXYZ(vec3 rotation) {
    mat4 rotationX = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, cos(rotation.x), -sin(rotation.x), 0.0,
        0.0, sin(rotation.x), cos(rotation.x), 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    mat4 rotationY = mat4(
        cos(rotation.y), 0.0, sin(rotation.y), 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sin(rotation.y), 0.0, cos(rotation.y), 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    mat4 rotationZ = mat4(
        cos(rotation.z), -sin(rotation.z), 0.0, 0.0,
        sin(rotation.z), cos(rotation.z), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    // Combine the rotations: rotationX * rotationY * rotationZ
    return rotationX * rotationY * rotationZ;
}

// Scaling Matrix
mat4 scaleMatrix(vec3 scale) {
    return mat4(
        scale.x, 0.0, 0.0, 0.0,
        0.0, scale.y, 0.0, 0.0,
        0.0, 0.0, scale.z, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

void main()
{
    uint index = gl_InstanceID;
    mat4 translationMatrix = mat4(1.0);
    mat4 rotaionMatrix = rotateXYZ(asteroidsData[index].rotation.xyz);
    mat4 scaleMatrix = scaleMatrix(asteroidsData[index].scale.xyz);
    translationMatrix *= scaleMatrix * translateMatrix(asteroidsData[index].position.xyz);
    translationMatrix *= model;
    Normal = transpose(inverse(mat3(translationMatrix))) * aNormal;
    TexCoords = aTexCoords;
    WorldPos = vec3(translationMatrix * vec4(aPos, 1.0));
    gl_Position = projection * view * vec4(WorldPos, 1.0f);
}