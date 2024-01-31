//
// Created by redkc on 14/12/2023.
//

#include "AsteroidsSystem.h"

AsteroidsSystem::AsteroidsSystem(Shader *asteroidShader) : asteroidShader(asteroidShader) {

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

void AsteroidsSystem::Draw(glm::mat4x4 transformationMatrix) {
    asteroidShader->use();
    asteroidShader->setMatrix4("model", false, glm::value_ptr(transformationMatrix));

    textures[0]->use(GL_TEXTURE3);
    textures[1]->use(GL_TEXTURE4);
    textures[2]->use(GL_TEXTURE5);
    textures[3]->use(GL_TEXTURE6);
    textures[4]->use(GL_TEXTURE7);

    for (unsigned int i = 0; i < asteroidModel.meshes.size(); i++) {
        glBindVertexArray(asteroidModel.meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(asteroidModel.meshes[i].indices.size()),
                                GL_UNSIGNED_INT, 0, asteroidsData.size());
        glBindVertexArray(0);
    }
}


void AsteroidsSystem::DrawToDepthMap(Shader *shader, glm::mat4x4 transformationMatrix) {
    shader->use();
    shader->setMatrix4("model", false, glm::value_ptr(transformationMatrix));

    for (unsigned int i = 0; i < asteroidModel.meshes.size(); i++) {
        glBindVertexArray(asteroidModel.meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(asteroidModel.meshes[i].indices.size()),
                                GL_UNSIGNED_INT, 0, asteroidsData.size());
        glBindVertexArray(0);
    }
}

void AsteroidsSystem::Init() {
    asteroidModel.loadModel();
    planet = glm::mat4x4(1);
    const float PI = 3.14159265359;
    float radius = 300;
    float span = 10;

    size = 3000;
    std::vector<glm::vec3> positions(size);
    std::vector<glm::vec3> rotations(size);
    std::vector<glm::vec3> velocities(size);
    std::vector<glm::vec3> angularVelocites(size);
    std::vector<glm::vec3> scales(size);


    for (int i = 0; i < size; ++i) {
        // Generate random positions
        float angle = glm::linearRand(0.0f, 2 * PI);
        float distance = glm::linearRand(radius, radius + span);
        
        float asteroidX = distance * sin(angle);
        float asteroidZ = distance * cos(angle);
        float asteroidY = glm::linearRand(-span * 5, span * 5);


        positions[i] = glm::vec3(asteroidX, asteroidY, asteroidZ);
        rotations[i] = glm::vec3(glm::linearRand(0.0f, 2 * PI));
        scales[i] = glm::vec3(glm::linearRand(minScale, maxScale));
        velocities[i] = glm::linearRand(glm::vec3(-0.5f), glm::vec3(0.5f));
        angularVelocites[i] = glm::linearRand(glm::vec3(-1), glm::vec3(1));

    }

    // Display generated positions and velocities
    for (int i = 0; i < size; ++i) {
        asteroidsData.push_back(
                AsteroidData(glm::vec4(positions[i], 1), glm::vec4(rotations[i], 1), glm::vec4(scales[i], 1),
                             glm::vec4(velocities[i], 1), glm::vec4(angularVelocites[i], 1), glm::vec4(0)));
    }

    GLuint currentId;
    glGenBuffers(1, &currentId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, currentId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, asteroidsData.size() * sizeof(AsteroidData), asteroidsData.data(),
                 GL_STREAM_DRAW);
    GLuint bindingPoint = 0; // Choose a binding point
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, currentId);

    glGenBuffers(1, &currentId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, currentId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, asteroidsData.size() * sizeof(CellData), nullptr,
                 GL_DYNAMIC_DRAW);
    bindingPoint = 1; // Choose a binding point
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, currentId);

    glGenBuffers(1, &currentId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, currentId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, asteroidsData.size() * sizeof(Offsets), nullptr,
                 GL_STREAM_DRAW);
    bindingPoint = 2; // Choose a binding point
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, currentId);

    shared_ptr<Texture> albedoMap = std::make_shared<Texture>("ocean-rock_albedo.png", "res/textures/ocean-rock-bl",
                                                              "texture_albedo");
    textures.insert(textures.end(), albedoMap);

    shared_ptr<Texture> normalMap = std::make_shared<Texture>("ocean-rock_normal-ogl.png", "res/textures/ocean-rock-bl",
                                                              "texture_albedo");
    textures.insert(textures.end(), normalMap);

    shared_ptr<Texture> metallicMap = std::make_shared<Texture>("ocean-rock_metallic.png", "res/textures/ocean-rock-bl",
                                                                "texture_albedo");
    textures.insert(textures.end(), metallicMap);

    shared_ptr<Texture> roughnessMap = std::make_shared<Texture>("ocean-rock_roughness.png",
                                                                 "res/textures/ocean-rock-bl", "texture_albedo");
    textures.insert(textures.end(), roughnessMap);

    shared_ptr<Texture> aoMap = std::make_shared<Texture>("ocean-rock_ao.png", "res/textures/ocean-rock-bl",
                                                          "texture_albedo");
    textures.insert(textures.end(), aoMap);

    textures[0]->use(GL_TEXTURE3);
    textures[1]->use(GL_TEXTURE4);
    textures[2]->use(GL_TEXTURE5);
    textures[3]->use(GL_TEXTURE6);
    textures[4]->use(GL_TEXTURE7);


    cumputeShaderMovment.init();
    cumputeShaderGridCreation.init();
    cumputeShaderGridCreation.use();
    float furthestPoint = (asteroidModel.futhestLenghtsFromCenter.x + asteroidModel.futhestLenghtsFromCenter.y +
                           asteroidModel.futhestLenghtsFromCenter.z) / 3;
    cumputeShaderGridCreation.setFloat("gridRadius", maxScale * furthestPoint * 2.0f);

    cumputeShaderGridSort.init();
    cumputeShaderGridSort.use();

    cumputeShaderGridCalculateOffset.init();
    cumputeShaderGridSort.use();

    cumputeShaderCollide.init();
    cumputeShaderCollide.use();
    cumputeShaderCollide.setFloat("collisionRadius", furthestPoint);
    cumputeShaderCollide.setFloat("gridRadius", maxScale * furthestPoint * 2.0f);

    cumputeShaderSeperation.init();
    cumputeShaderSeperation.use();
}

void AsteroidsSystem::Update(float deltaTime) {
    cumputeShaderMovment.use();
    cumputeShaderMovment.setFloat("deltaTime", deltaTime);
    glDispatchCompute(asteroidsData.size(), 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    cumputeShaderGridCreation.use();
    glDispatchCompute(asteroidsData.size(), 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    cumputeShaderGridSort.use();
    int numPairs = nextPowerOfTwo(asteroidsData.size()) / 2;
    int numStages = (int) glm::log2((float) numPairs * 2);
    for (int stageIndex = 0; stageIndex < numStages; stageIndex++) {
        for (int stepIndex = 0; stepIndex < stageIndex + 1; stepIndex++) {
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
    glDispatchCompute(asteroidsData.size(), 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);


    cumputeShaderCollide.use();
    glDispatchCompute(asteroidsData.size(), 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    cumputeShaderSeperation.use();
    glDispatchCompute(asteroidsData.size(), 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}
