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
    glDispatchCompute(1, 1 , 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    cumputeShaderGridCalculateOffset.use();
    glDispatchCompute(size, 1 , 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    
    asteroidShader.use();
    for (unsigned int i = 0; i < asteroidModel.meshes.size(); i++)
    {
        glBindVertexArray (asteroidModel.meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(asteroidModel.meshes[i].indices.size()), GL_UNSIGNED_INT, 0, asteroidsData.size());
        glBindVertexArray(0);
    }
}

void AsteroidsSystem::Init() {
    asteroidModel.loadModel();

    float radius = 60.0;
    float offset = 60.0f;

    for (unsigned int i = 0; i < size; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float)i / (float) size * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        
        glm::vec4 position = glm::vec4(x, y, z,1);
        glm::vec4 rotation = glm::vec4(glm::linearRand(glm::vec3(-0.5f),glm::vec3(0.5f)),1);
        glm::vec4 scale =  glm::vec4(glm::linearRand(glm::vec3(0.5f),glm::vec3(2.0f)),1);
        glm::vec4 velocity = glm::vec4(glm::linearRand(glm::vec3(-0.5f),glm::vec3(0.5f)),1);
        glm::vec4 angularVelocity =glm::vec4( glm::linearRand(glm::vec3(-0.5f),glm::vec3(0.5f)),1);
        
        asteroidsData.push_back(AsteroidData(position,rotation,scale,velocity,angularVelocity));
    }


    GLuint currentId;
    glGenBuffers(1, &currentId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, currentId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, asteroidsData.size() * sizeof(AsteroidData), asteroidsData.data(), GL_STATIC_DRAW);
    GLuint bindingPoint = 0; // Choose a binding point
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, currentId);
    
    glGenBuffers(1, &currentId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, currentId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, asteroidsData.size() * sizeof(CellData), asteroidsData.data(), GL_STATIC_DRAW);
    bindingPoint = 1; // Choose a binding point
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, currentId);


    asteroidShader.init();
    asteroidShader.use();
    asteroidShader.setInt("material.diffuse1", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, asteroidModel.textures_loaded[0]->ID); // note: we also made the textures_loaded vector public (instead of private) from the model class.

    cumputeShaderMovment.init();
    cumputeShaderGridCreation.init();
    cumputeShaderGridCreation.use();
    float furthestPoint = (asteroidModel.futhestLenghtsFromCenter.x + asteroidModel.futhestLenghtsFromCenter.y + asteroidModel.futhestLenghtsFromCenter.z)/3;
    cumputeShaderGridCreation.setFloat("collisonRadius", furthestPoint * 2);
    cumputeShaderGridCreation.setInt("asteroidCount", size);


    int currentWorkSize;
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE,0,&currentWorkSize); //Assign max work size to the work size
    int numPairs = nextPowerOfTwo(size) / 2;
    while (numPairs % currentWorkSize != 0){ //Essentialy making sure that we can easly iterate over the data
        currentWorkSize/=2;
    }
    cumputeShaderGridSort.setLayout((int)currentWorkSize,1,1);
    cumputeShaderGridSort.init();
    cumputeShaderGridSort.use();
    //int numPairs = nextPowerOfTwo(size) / 2;
    int numStages = (int) glm::log2((float)numPairs * 2);
    cumputeShaderGridSort.setInt("numStages",numStages);
    cumputeShaderGridSort.setInt("numOfIterations", (int)size/currentWorkSize);

    cumputeShaderGridCalculateOffset.init();
    cumputeShaderGridSort.use();
}
