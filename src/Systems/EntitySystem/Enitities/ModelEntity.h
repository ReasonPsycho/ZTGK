//
// Created by redkc on 18/02/2024.
//

#ifndef REASONABLEGL_MODELENTITY_H
#define REASONABLEGL_MODELENTITY_H


#include "Enitity.h"

class ModelEntity : public Entity{
    
public:
    ModelEntity(Model *pModel);
    ModelEntity(Entity* parent,Model *pModel);
    void draw(Shader &regularShader) override;
    void draw(Shader &regularShader,Shader &instancedShader) override;
    Model *pModel;
};




#endif //REASONABLEGL_MODELENTITY_H
