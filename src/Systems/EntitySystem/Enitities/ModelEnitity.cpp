//
// Created by redkc on 18/02/2024.
//

#include "ModelEntity.h"

ModelEntity::ModelEntity(Model *pModel) : pModel(pModel) {

}

ModelEntity::ModelEntity(Entity *parent, Model *pModel) :pModel(pModel), Entity(parent) {

}

void  ModelEntity::draw(Shader &regularShader)  {
    regularShader.setMatrix4("model", false, glm::value_ptr(transform.getModelMatrix()));
    pModel->Draw(regularShader);
}

void ModelEntity::draw(Shader &regularShader,Shader &instancedShader) {
    regularShader.setMatrix4("model", false, glm::value_ptr(transform.getModelMatrix()));
    pModel->Draw(regularShader);
}