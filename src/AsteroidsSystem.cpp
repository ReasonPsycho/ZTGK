//
// Created by redkc on 14/12/2023.
//

#include "AsteroidsSystem.h"

AsteroidsSystem::AsteroidsSystem(int size) : size(size) {

}

unsigned int nextPowerOfTwo(unsigned int n) {
    // If n is already a power of two, return it
    if (n && !(n & (n - 1)))
        return n;

    // Find the position of the most significant bit (MSB)
    unsigned int count = 0;
    while (n != 0) {
        n >>= 1;
        count++;
    }

    // The power of two will have only the MSB set, so left shift 1 to the left by count positions
    return 1 << count;
}

void AsteroidsSystem::Draw(float deltaTime) {

    cumputeShaderMovment.use();
    cumputeShaderMovment.setFloat("deltaTime", deltaTime);
    glDispatchCompute(size, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    cumputeShaderGridCreation.use();
    glDispatchCompute(size, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    cumputeShaderGridSort.use();
    int numPairs = nextPowerOfTwo(size) / 2;
    int numStages = (int) glm::log2((float) numPairs * 2);
    for (int stageIndex = 0; stageIndex < numStages; stageIndex++)
    {
        for (int stepIndex = 0; stepIndex < stageIndex + 1; stepIndex++)
        {
            // Calculate some pattern stuff
            int groupWidth = 1 << (stageIndex - stepIndex);
            int groupHeight = 2 * groupWidth - 1;
            cumputeShaderGridSort.setInt("groupWidth", groupWidth);
            cumputeShaderGridSort.setInt("groupHeight", groupHeight);
            cumputeShaderGridSort.setInt("stepIndex", stepIndex);
            // Run the sorting step on the GPU
            glDispatchCompute(numPairs, 1, 1);
            glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
        }
    }

    cumputeShaderGridCalculateOffset.use();
    glDispatchCompute(size, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    
    
    cumputeShaderCollide.use();
    glDispatchCompute(size, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    cumputeShaderSeperation.use();
    glDispatchCompute(size, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    asteroidShader.use();
    for (unsigned int i = 0; i < asteroidModel.meshes.size(); i++) {
        glBindVertexArray(asteroidModel.meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(asteroidModel.meshes[i].indices.size()),
                                GL_UNSIGNED_INT, 0, asteroidsData.size());
        glBindVertexArray(0);
    }

   // glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
   // gridLinesShader.use();
}

void AsteroidsSystem::Init() {
    asteroidModel.loadModel();

    
    size = 20;
    std::vector<glm::vec3> positions(size);
    std::vector<glm::vec3> velocities(size);
    std::vector<glm::vec3> scales(size);

    glm::vec4 rotation = glm::vec4(1,1,1, 1);
    glm::vec4 angularVelocity = glm::vec4(0,0,0, 1);
    
    glm::vec3 center = glm::vec3(-5);
    
    for (int i = 0; i < size; ++i) {
        // Generate random positions
        positions[i] = glm::sphericalRand(10.0f) + center; // Random positions within a sphere of radius 100
        scales[i] = glm::vec3(glm::linearRand(minScale, maxScale));
        // Calculate velocity towards the origin (0, 0, 0)
        glm::vec3 directionToOrigin = glm::normalize(center - positions[i]);
        float speed = glm::linearRand(1.0f, 2.0f); // Random speed between 1 and 5 units per frame
        velocities[i] = directionToOrigin * speed;
    }

    // Display generated positions and velocities
    for (int i = 0; i < size; ++i) {
        asteroidsData.push_back(AsteroidData(glm::vec4 (positions[i],1), rotation, glm::vec4 (scales[i],1), glm::vec4 (velocities[i],1), angularVelocity));
    }
    
    /*
    float radius = 40.0;
    float offset = 20.0f;

    for (unsigned int i = 0; i < size; i++) {
        glm::mat4 model = glm::mat4(1.0f);

        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float) i / (float) size * 360.0f;
        float displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;

        glm::vec4 position = glm::vec4(x, y, z, 1);
        glm::vec4 rotation = glm::vec4(glm::linearRand(glm::vec3(-0.5f), glm::vec3(0.5f)), 1);
        glm::vec4 scale = glm::vec4(glm::linearRand(glm::vec3(1.0f), glm::vec3(1.0f)), 1);
        glm::vec4 velocity = glm::vec4(glm::linearRand(glm::vec3(-0.5f), glm::vec3(0.5f)), 1);
        glm::vec4 angularVelocity = glm::vec4(glm::linearRand(glm::vec3(-0.5f), glm::vec3(0.5f)), 1);

        asteroidsData.push_back(AsteroidData(position, rotation, scale, velocity, angularVelocity));
    }
    */

    GLuint currentId;
    glGenBuffers(1, &currentId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, currentId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, asteroidsData.size() * sizeof(AsteroidData), asteroidsData.data(),
                 GL_STATIC_DRAW);
    GLuint bindingPoint = 0; // Choose a binding point
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, currentId);

    glGenBuffers(1, &currentId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, currentId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, asteroidsData.size() * sizeof(CellData), asteroidsData.data(),
                 GL_STATIC_DRAW);
    bindingPoint = 1; // Choose a binding point
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, currentId);

    glGenBuffers(1, &currentId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, currentId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, asteroidsData.size() * sizeof(Offsets), asteroidsData.data(),
                 GL_STATIC_DRAW);
    bindingPoint = 2; // Choose a binding point
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, currentId);
    
    gridLinesShader.init();
    gridLinesShader.use();

    asteroidShader.init();
    asteroidShader.use();
    asteroidShader.setInt("material.diffuse1", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,
                  asteroidModel.textures_loaded[0]->ID); // note: we also made the textures_loaded vector public (instead of private) from the model class.

    cumputeShaderMovment.init();
    cumputeShaderGridCreation.init();
    cumputeShaderGridCreation.use();
    float furthestPoint = (asteroidModel.futhestLenghtsFromCenter.x + asteroidModel.futhestLenghtsFromCenter.y +
                           asteroidModel.futhestLenghtsFromCenter.z) / 3;
    cumputeShaderGridCreation.setFloat("gridRadius", maxScale * furthestPoint);
    
    cumputeShaderGridSort.init();
    cumputeShaderGridSort.use();

    cumputeShaderGridCalculateOffset.init();
    cumputeShaderGridSort.use();

    cumputeShaderCollide.init();
    cumputeShaderCollide.use();
    cumputeShaderCollide.setFloat("collisionRadius", furthestPoint);
    cumputeShaderCollide.setFloat("gridRadius", maxScale * furthestPoint);

    cumputeShaderSeperation.init();
    cumputeShaderSeperation.use();
}
