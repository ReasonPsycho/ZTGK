//
// Created by redkc on 18/05/2024.
//
#include "TextureArray.h"

TextureArray::TextureArray(std::vector<shared_ptr<Texture>> textures) {
    
// Generate the GL_TEXTURE_2D_ARRAY
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, textures[0]->format, textures[0]->width,  textures[0]->height,textures.size(),0, textures[0]->format,GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);


// Attach the 2D textures to the array
    for (GLuint i = 0; i < textures.size(); ++i)
    {
        glBindTexture(GL_TEXTURE_2D,  textures[i]->ID);

        // Allocate memory for the texture and bind its data to the texture array
        vector<GLubyte> texData(textures[i]->width * textures[i]->height *  textures[i]->nrChannels * sizeof(GLuint) ) ; // Assuming 4 channels of data, adjust as necessary
        glGetTexImage(GL_TEXTURE_2D, 0, textures[i]->format, GL_UNSIGNED_BYTE, texData.data());
        glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, textures[i]->width, textures[i]->height, 1, textures[i]->format, GL_UNSIGNED_BYTE, texData.data());
    }

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        // Process/log the error.
        std::cout << "OpenGL error: " << err << std::endl;
    }
}
