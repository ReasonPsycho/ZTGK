//
// Created by redkc on 30/01/2024.
//

#ifndef OPENGLGP_SHADOW_H
#define OPENGLGP_SHADOW_H


class Shadow {
public:
    void Init();

    ~Shadow();

private:
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMapFBO;
    unsigned int depthCubemap;
};


#endif //OPENGLGP_SHADOW_H
