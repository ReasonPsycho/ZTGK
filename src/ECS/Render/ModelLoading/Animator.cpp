//
// Created by redkc on 09/06/2024.
//

#include "Animator.h"

Animator::Animator(Animation *animation) {
    m_CurrentTime = 0.0;
    m_CurrentAnimation = animation;

    m_FinalBoneMatrices.reserve(100);
    m_FinalNodeMatrices.reserve(100);

    for (int i = 0; i < 100; i++) {
        m_FinalBoneMatrices.push_back(glm::mat4(1.0f));
        m_FinalNodeMatrices.push_back(glm::mat4(1.0f));
    }

}

void Animator::UpdateAnimation(float dt) {
    m_DeltaTime = dt;
    if (m_CurrentAnimation) {
        m_CurrentTime += m_CurrentAnimation->GetTicksPerSecond() * dt;
        CalculateBoneTransform(&m_CurrentAnimation->GetRootNode(), glm::mat4(1.0f));
    }
}

void Animator::PlayAnimation(Animation *pAnimation) {
    m_CurrentAnimation = pAnimation;
    m_CurrentTime = 0.0f;
}

void Animator::CalculateBoneTransform(const AssimpNodeData *node, glm::mat4 parentTransform) {
    std::string nodeName = node->name;
    glm::mat4 nodeTransform = node->transformation;
    Bone *Bone = m_CurrentAnimation->FindBone(nodeName);

    if (Bone) {
        Bone->Update(fmod(m_CurrentTime, m_CurrentAnimation->GetDuration()));
        nodeTransform = Bone->GetLocalTransform();
    }

    glm::mat4 globalTransformation = parentTransform * nodeTransform;

    auto boneInfoMap = m_CurrentAnimation->GetBoneIDMap();
    if (boneInfoMap.find(nodeName) != boneInfoMap.end()) {
        int index = boneInfoMap[nodeName].id;
        glm::mat4 offset = boneInfoMap[nodeName].offset;
        m_FinalBoneMatrices[index] = globalTransformation * offset;
    }

    for (int i = 0; i < node->childrenCount; i++)
        CalculateBoneTransform(&node->children[i], globalTransformation);
}

void Animator::CalculateNodeTransform(const AssimpNodeData *node, glm::mat4 parentTransform) {
    std::string nodeName = node->name;
    glm::mat4 nodeTransform = node->transformation;
    glm::mat4 boneTransform = glm::mat4(1);
    Bone *Bone = m_CurrentAnimation->FindBone(nodeName);

    if (Bone) {
        Bone->Update(fmod(m_CurrentTime, m_CurrentAnimation->GetDuration()));
        boneTransform = Bone->GetLocalTransform();
    }
    
    glm::mat4 globalTransformation = parentTransform * boneTransform;

    auto boneInfoMap = m_CurrentAnimation->GetBoneIDMap();
    if (boneInfoMap.find(nodeName) != boneInfoMap.end()) {
        int index = boneInfoMap[nodeName].id;
        glm::mat4 offset = boneInfoMap[nodeName].offset;

        m_FinalNodeMatrices[index] = globalTransformation * boneTransform * offset;
        
    }

    for (int i = 0; i < node->childrenCount; i++) {
        CalculateNodeTransform(&node->children[i], globalTransformation);
    }
}

std::vector<glm::mat4> Animator::GetFinalBoneMatrices() {
    return m_FinalBoneMatrices;
}

std::vector<glm::mat4> Animator::GetFinalNodeMatrices() {
    return m_FinalNodeMatrices;
}

void Animator::UpdateNodes() {
    if (m_CurrentAnimation) {
        CalculateNodeTransform(&m_CurrentAnimation->GetRootNode(), glm::mat4(1.0f));
    }
}
