//
// Created by redkc on 30/01/2024.
//

#include "Transform.h"


glm::mat4 Transform::getLocalModelMatrix() {
    glm::mat4 rotationMatrix = glm::toMat4(m_quaternion);
    // translation * rotation * scale (also know as TRS matrix)
    return glm::translate(glm::mat4(1.0f), m_pos) * rotationMatrix * glm::scale(glm::mat4(1.0f), m_scale);
}


glm::mat4 Transform::getLocalTranslationMatrix() {
    glm::mat4 rotationMatrix = glm::toMat4(m_quaternion);


    // translation * rotation * scale (also know as TRS matrix)
    return glm::translate(glm::mat4(1.0f), m_pos) * rotationMatrix * glm::scale(glm::mat4(1.0f), glm::vec3(1));
}

void Transform::computeModelMatrix() {
    m_modelMatrix = getLocalModelMatrix();
    m_isDirty = false;
}

void Transform::computeModelMatrix(const glm::mat4 &parentGlobalModelMatrix) {
    m_modelMatrix = parentGlobalModelMatrix * getLocalModelMatrix();
    m_parentMatrix = parentGlobalModelMatrix;
    m_isDirty = false;
}

void Transform::setLocalPosition(const glm::vec3 &newPosition) {
    m_pos = newPosition;
    m_isDirty = true;
}

void Transform::setLocalRotation(const glm::quat &newRotation) {
    m_quaternion = newRotation;
    m_isDirty = true;
}

void Transform::setLocalScale(const glm::vec3 &newScale) {
    m_scale = newScale;
    m_isDirty = true;
}

const glm::vec3 Transform::getGlobalPosition() const { return m_modelMatrix[3]; }

const glm::vec3 &Transform::getLocalPosition() const {
    return m_pos;
}

const glm::quat &Transform::getLocalRotation() const {
    return m_quaternion;
}

const glm::vec3 &Transform::getLocalScale() const {
    return m_scale;
}

const glm::mat4 &Transform::getModelMatrix() const {
    return m_modelMatrix;
}

glm::vec3 Transform::getRight() const {
    return m_modelMatrix[0];
}

glm::vec3 Transform::getUp() const {
    return m_modelMatrix[1];
}

glm::vec3 Transform::getBackward() const {
    return m_modelMatrix[2];
}

glm::vec3 Transform::getForward() const {
    return -m_modelMatrix[2];
}

glm::vec3 Transform::getGlobalScale() const {
    return {glm::length(getRight()), glm::length(getUp()), glm::length(getBackward())};
}

bool Transform::isDirty() const {
    return m_isDirty;
}

void Transform::ManipulateModelMatrix(Camera *camera) {
    static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::ROTATE);
    static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);
    if (ImGui::IsKeyPressed(ImGuiKey_G))
        mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
    if (ImGui::IsKeyPressed(ImGuiKey_S))
        mCurrentGizmoOperation = ImGuizmo::ROTATE;
    if (ImGui::IsKeyPressed(ImGuiKey_R)) // r Key
        mCurrentGizmoOperation = ImGuizmo::SCALE;
    if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
        mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
        mCurrentGizmoOperation = ImGuizmo::ROTATE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
        mCurrentGizmoOperation = ImGuizmo::SCALE;
    
    mCurrentGizmoMode = ImGuizmo::WORLD;
    /* This is confusing for now maby to imolement later
    if (mCurrentGizmoOperation != ImGuizmo::SCALE)
    {
        if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
            mCurrentGizmoMode = ImGuizmo::LOCAL;
        ImGui::SameLine();
        if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
            mCurrentGizmoMode = ImGuizmo::WORLD;
    }
    */
    /* Maby someday I will implement snap
    static bool useSnap(false);
    if (ImGui::IsKeyPressed(ImGuiKey_LeftCtrl))
        useSnap = !useSnap;
    ImGui::Checkbox("", &useSnap);
    ImGui::SameLine();
    glm::vec3 snap;
    switch (mCurrentGizmoOperation)
    {
        case ImGuizmo::TRANSLATE:
            snap = game.mSnapTranslation;
            ImGui::InputFloat3("Snap", &snap.x);
            break;
        case ImGuizmo::ROTATE:
            snap = game.mSnapRotation;
            ImGui::InputFloat("Angle Snap", &snap.x);
            break;
        case ImGuizmo::SCALE:
            snap = game.mSnapScale;
            ImGui::InputFloat("Scale Snap", &snap.x);
            break;
    }
     */
    ImGuiIO& io = ImGui::GetIO();
    ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);


    glm::mat4 tmp_matrix = getModelMatrix();
    glm::mat4 deltaMatrix = glm::mat4(1.0f);

    ImGuizmo::Manipulate(glm::value_ptr(camera->GetViewMatrix()), glm::value_ptr(camera->GetProjectionMatrix()), mCurrentGizmoOperation, mCurrentGizmoMode, glm::value_ptr(tmp_matrix), glm::value_ptr(deltaMatrix), NULL);
    glm::vec3 outTranslation;
    glm::vec3 outRotation;
    glm::vec3 outScale;

    tmp_matrix = glm::inverse(m_parentMatrix) * tmp_matrix;
    ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(tmp_matrix), glm::value_ptr(outTranslation), glm::value_ptr(outRotation), glm::value_ptr(outScale));

    ImGui::InputFloat3("Tr", glm::value_ptr(outTranslation));
    ImGui::InputFloat3("Rt", glm::value_ptr(outRotation));
    ImGui::InputFloat3("Sc", glm::value_ptr(outScale));

    if (deltaMatrix != glm::mat4(1.0f)  || m_pos != outTranslation || m_quaternion !=glm::quat(glm::radians(outRotation)) || m_scale != outScale) {
        
        // Set the new local transform components
        m_pos = outTranslation;
        m_quaternion = glm::quat(glm::radians(outRotation)); // assuming outRotation is in degrees
        m_scale = outScale;

        m_isDirty = true;
    }
}

const glm::quat &Transform::getGlobalRotation() const {
    return glm::quat_cast(m_modelMatrix);
}

void decomposeMtx(const glm::mat4& m, glm::vec3& pos, glm::quat& rot, glm::vec3& scale)
{
    pos = m[3];
    for(int i = 0; i < 3; i++)
        scale[i] = glm::length(glm::vec3(m[i]));
    const glm::mat3 rotMtx(
            glm::vec3(m[0]) / scale[0],
            glm::vec3(m[1]) / scale[1],
            glm::vec3(m[2]) / scale[2]);
    rot = glm::quat_cast(rotMtx);
}

void Transform::setLocalMatrix(const glm::mat4 &transformMatrix) {
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;

    decomposeMtx(transformMatrix,translation, rotation, scale);
  //  translation.z += 2;
 //   translation.y += 0.5;
    setLocalRotation(rotation);
    setLocalPosition(translation);
    setLocalScale(scale);
}



