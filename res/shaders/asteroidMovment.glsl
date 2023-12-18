#version 430

layout (local_size_x = 10, local_size_y = 1, local_size_z = 1) in;


struct AsteroidData
{
    vec4 position;
    vec4 rotation;
    vec4 scale;
    vec4 velocity;
    vec4 angularVelocity;
};

layout (std430, binding = 0) buffer AsteroidBuffer {
    AsteroidData asteroidsData[]; // Array of velocities
};

uniform float deltaTime;

void main() {
    uint index = gl_GlobalInvocationID.x;

    // Perform operations on particles based on index
    asteroidsData[index].position.xyz += (asteroidsData[index].velocity.xyz * vec3(deltaTime));
    asteroidsData[index].rotation.xyz += (asteroidsData[index].angularVelocity.xyz* vec3(deltaTime));
}