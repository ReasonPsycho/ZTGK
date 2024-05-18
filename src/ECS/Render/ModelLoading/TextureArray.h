//
// Created by redkc on 18/05/2024.
//

#ifndef ZTGK_TEXTUREARRAY_H
#define ZTGK_TEXTUREARRAY_H

#include "Texture.h"

using namespace std;


class TextureArray {
    public:
    TextureArray(std::vector<shared_ptr<Texture>> textures);
    GLuint ID{};

};

#endif //ZTGK_TEXTUREARRAY_H
