#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out flat int[4] currentTextures;
out VS_OUT {
    vec2 TexCoords;
    vec3 Normal;
    vec3 WorldPos;
    vec3 ViewPos;
}vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 camPos;
uniform vec3 cameraUp;

struct ParticleData
{
    int data[4];// nothing yet , nothing yet, 2 bilborded, 3 texture
    vec4 position; // 4th is for lifeTime
    vec4 rotation; // 4th is for time to live
    vec4 scale;// 4th is for gravity
    vec4 velocity;
    vec4 angularVelocity;
};

layout (std430, binding = 10) buffer AsteroidBuffer {
    ParticleData particleData[];// Array of velocities
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

    //Instance shader set up
    uint index = gl_InstanceID;
    ParticleData currentParticle = particleData[index];

    currentTextures[0] = currentParticle.data[3];
    
    mat4 model = mat4(1);
    
    mat4 locScaleMatrix = scaleMatrix(currentParticle.scale.xyz);
    if (currentParticle.data[2] == 1){
        vec3 look = normalize(camPos - currentParticle.position.xyz);
        vec3 right = cross(cameraUp, look);
        model[0] = vec4(right, 0.0);
        model[1] = vec4(cameraUp, 0.0);
        model[2] = vec4(look, 0.0);
        model[3] = vec4(currentParticle.position.xyz, 1.0);
        model*= locScaleMatrix;
    } else {
        model[3] = currentParticle.position;
        mat4 rotaionMatrix = rotateXYZ(currentParticle.rotation.xyz);
        model *= locScaleMatrix * rotaionMatrix;
    }
    
    
    
    //Standard calculation
    vs_out.TexCoords = aTexCoords;
    vs_out.WorldPos = vec3(model* vec4(aPos, 1.0));
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;
    vs_out.ViewPos = camPos;
    gl_Position = projection * view * vec4(vs_out.WorldPos, 1.0);
}
