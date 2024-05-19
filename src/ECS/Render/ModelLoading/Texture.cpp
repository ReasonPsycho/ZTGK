#include "Texture.h"


void Texture::use(GLenum GL_TEXTUREX) {
    glActiveTexture(GL_TEXTUREX);
    glBindTexture(GL_TEXTURE_2D, ID);
}

Texture::~Texture() {
    glDeleteTextures(1, &ID);
}

Texture::Texture(string path, string type) {
    glGenTextures(1, &ID);
    // set the texture wrapping/filtering options (on the currently bound texture object) //TODO this prob should be in class inputs
    // load and generate the texture
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        if (nrChannels == 1) //nifty 
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, ID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        name = path.substr(path.find_last_of('/') + 1);
        this->path = path;
        this->type = type;
    } else {
        spdlog::error("Failed to load texture: " + path + ". Defaulting to black pixel.");
        Texture();
    }
}

Texture::Texture(const Color& color) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, color);

    // Set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
