#version 430

layout (local_size_x = 10, local_size_y = 1, local_size_z = 1) in;


struct AsteroidData
{
    mat4 model;
    vec4 velocity;
    vec4 rotation;
};

layout (std430, binding = 0) buffer AsteroidBuffer {
    AsteroidData asteroidsData[]; // Array of velocities
};

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


void main() {
    uint index = gl_GlobalInvocationID.x;

    // Perform operations on particles based on index
    mat4 translation = translateMatrix(asteroidsData[index].velocity.xyz);
    mat4 rotation = rotateXYZ(asteroidsData[index].rotation.xyz);
    asteroidsData[index].model *= translation;
    asteroidsData[index].model *= rotation;
}