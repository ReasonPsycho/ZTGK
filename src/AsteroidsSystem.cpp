//
// Created by redkc on 14/12/2023.
//

#include "AsteroidsSystem.h"

AsteroidsSystem::AsteroidsSystem(int size) : size(size) {
    
}

void AsteroidsSystem::Draw() {
    
    
    computeShader.use();
    glDispatchCompute(size, 1, 1);

    // Ensure memory barriers after the compute shader finishes
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
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
        model = glm::scale(model, glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = static_cast<float>((rand() % 360));
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        glm::vec4 velocity = glm::linearRand(glm::vec4(0.01f),glm::vec4(0.05f));
        glm::vec4 rotation = glm::linearRand(glm::vec4(0.01f),glm::vec4(0.05f));
        // 4. now add to list of matrices
        asteroidsData.push_back(AsteroidData(model,velocity,rotation));
    }

    
    
    glGenBuffers(1, &ID);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);

    // Allocate space for the buffer based on the size of the vector
    glBufferData(GL_SHADER_STORAGE_BUFFER, asteroidsData.size() * sizeof(AsteroidData), asteroidsData.data(), GL_STATIC_DRAW);

    // Bind the buffer to a binding point
    GLuint bindingPoint = 0; // Choose a binding point
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, ID);

    asteroidShader.init();
    asteroidShader.use();
    asteroidShader.setInt("material.diffuse1", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, asteroidModel.textures_loaded[0]->ID); // note: we also made the textures_loaded vector public (instead of private) from the model class.

    computeShader.init();
    
   
}
