//
// Created by redkc on 30/01/2024.
//

#ifndef OPENGLGP_TRANSFORM_H
#define OPENGLGP_TRANSFORM_H

#include <glm/glm.hpp> //glm::mat4
#include <list> //std::list
#include <array> //std::array
#include <memory> //std::unique_ptr
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/quaternion.hpp"
#include "imgui.h"
#include "ImGuizmo.h"
#include "ECS/Render/Camera/Camera.h"
#include <glm/gtx/matrix_decompose.hpp>

class Transform {
protected:
    //Local space information
    glm::vec3 m_pos = {0.0f, 0.0f, 0.0f};
    glm::quat m_quaternion = glm::quat(); //In degrees
    glm::vec3 m_scale = {1.0f, 1.0f, 1.0f};

    //Global space information concatenate in matrix
    glm::mat4 m_modelMatrix = glm::mat4(1.0f);
    glm::mat4 m_parentMatrix = glm::mat4(1.0f);
    //Dirty flag
    bool m_isDirty = true;

public:
    Transform() = default;
    void ManipulateModelMatrix(Camera* camera);
    void computeModelMatrix();

    void computeModelMatrix(const glm::mat4 &parentGlobalModelMatrix);

    void setLocalPosition(const glm::vec3 &newPosition);

    void setLocalRotation(const glm::quat &newRotation);

    void setLocalScale(const glm::vec3 &newScale);

    const glm::vec3 getGlobalPosition() const;

    const glm::vec3 &getLocalPosition() const;
    
    void  setLocalMatrix(const glm::mat4& transformMatrix);

    const glm::quat &getLocalRotation() const;
    
    const glm::quat &getGlobalRotation() const;

    const glm::vec3 &getLocalScale() const;

    const glm::mat4 &getModelMatrix() const;

    glm::vec3 getRight() const;


    glm::vec3 getUp() const;

    glm::vec3 getBackward() const;

    glm::vec3 getForward() const;

    glm::vec3 getGlobalScale() const;

    bool isDirty() const;

    glm::mat4 getLocalModelMatrix();

    glm::mat4 getLocalTranslationMatrix();

    glm::mat4 getLocalToChildMatrix(Transform &childTransform);
};


#endif //OPENGLGP_TRANSFORM_H
