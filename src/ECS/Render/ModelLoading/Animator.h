//
// Created by redkc on 09/06/2024.
//

#ifndef ZTGK_ANIMATOR_H
#define ZTGK_ANIMATOR_H

#include "Animation.h"
#include <glm/glm.hpp>
#include <future>

class Animator
{
public:
    Animator(Animation* animation);

    void UpdateAnimation(float dt);
    void UpdateNodes();

    void PlayAnimation(Animation* pAnimation);

    void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);
    void CalculateNodeTransform(const AssimpNodeData* node, glm::mat4 parentTransform);

    std::vector<glm::mat4> GetFinalBoneMatrices();
    std::vector<glm::mat4> GetFinalNodeMatrices();
    
    Animation* m_CurrentAnimation;

    float m_CurrentTime;

private:
    std::vector<glm::mat4> m_FinalBoneMatrices;
    std::vector<glm::mat4> m_FinalNodeMatrices;
    float m_DeltaTime;
};


#endif //ZTGK_ANIMATOR_H
