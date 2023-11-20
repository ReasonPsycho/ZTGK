//
// Created by redkc on 20/11/2023.
//

#include "Cube.h"
#include "Utilities/Shader.h"
#include "Utilities/Texture.h"


Cube::Cube()  {
    model = glm::mat4(1.0f);
}

void Cube::init() {
    float vertices[] = {
            // Front face
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom left
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  // bottom right
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // top right
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  // top left

            // Back face
            -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom left
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // bottom right
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f,   // top right
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  // top left

            // Left face
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom left
            -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  // bottom right
            -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // top right
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  // top left

            // Right face
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom left
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // bottom right
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f,   // top right
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  // top left

            // Top face
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  // bottom left
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // bottom right
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f,  // top right
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, // top left

            // Bottom face
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // bottom left
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   // bottom right
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  // top right
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top left
    };
    unsigned int indices[] = {
            // Front face
            0, 1, 2,
            2, 3, 0,

            // Back face
            4, 5, 6,
            6, 7, 4,

            // Left face
            8, 9, 10,
            10, 11, 8,

            // Right face
            12, 13, 14,
            14, 15, 12,

            // Top face
            16, 17, 18,
            18, 19, 16,

            // Bottom face
            20, 21, 22,
            22, 23, 20
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // Position attribute
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // Texture coordinate attribute
    glEnableVertexAttribArray(1);
}

Cube::~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Cube::render(Shader shader,Texture texture) {
    texture.use();
    shader.use(); //Don't need this yet tbh
    model = glm::rotate(model,0.001f, glm::vec3(1, 1, 1)) ;
    shader.setMatrix4("transform",false, glm::value_ptr(model));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);
}
