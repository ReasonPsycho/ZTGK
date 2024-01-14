#version 430

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

struct AsteroidData {
    vec4 position;
    vec4 rotation;
    vec4 scale;
    vec4 velocity;
    vec4 angularVelocity;
    vec4 separationVector;
    vec4 changeInVelocity;
    vec4 changeInAngularVelocity;
};

layout (std430, binding = 0) buffer AsteroidBuffer {
    AsteroidData asteroidsData[]; // Array of velocities
};

float MeanOfScales(vec3 scale) {
    return dot(scale, vec3(1.0)) / 3.0;
}

void main() {
    uint index = gl_WorkGroupID .x;
    if(asteroidsData[index].separationVector.xyz != vec3(0)){
        asteroidsData[index].position.xyz += asteroidsData[index].separationVector.xyz ;
        asteroidsData[index].velocity.xyz = asteroidsData[index].changeInVelocity.xyz ;
        asteroidsData[index].angularVelocity.xyz = asteroidsData[index].changeInAngularVelocity.xyz ;
    }
}