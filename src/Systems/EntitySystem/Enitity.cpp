//
// Created by redkc on 10/01/2024.
//
#include "Enitity.h"



void Entity::drawSelfAndChild(Shader &ourShader, unsigned int &display, unsigned int &total) {
    ourShader.setMatrix4("model", false, glm::value_ptr(transform.getModelMatrix()));
    draw(ourShader);
    display++;
    total++;

    for (auto &&child: children) {
        child->drawSelfAndChild(ourShader, display, total);
    }
}

void Entity::forceUpdateSelfAndChild() {
    if (parent)
        transform.computeModelMatrix(parent->transform.getModelMatrix());
    else
        transform.computeModelMatrix();

    for (auto &&child: children) {
        child->forceUpdateSelfAndChild();
    }
}

void Entity::updateSelfAndChild() {
    if (transform.isDirty()) {
        forceUpdateSelfAndChild();
        return;
    }

    for (auto &&child: children) {
        child->updateSelfAndChild();
    }
}

void Entity::draw(Shader &ourShader) {
    ourShader.setMatrix4("model", false, glm::value_ptr(transform.getModelMatrix()));
    pModel->Draw(ourShader);
}
