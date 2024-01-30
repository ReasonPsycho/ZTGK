//
// Created by redkc on 30/01/2024.
//

#ifndef OPENGLGP_SHADOWSYSTEM_H
#define OPENGLGP_SHADOWSYSTEM_H


class ShadowSystem {

public:
    void Init(float SHADOW_WIDTH, float SHADOW_HEIGHT);
    unsigned int depthMapFBO;
};


#endif //OPENGLGP_SHADOWSYSTEM_H
