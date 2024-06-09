//
// Created by redkc on 09/06/2024.
//

#ifndef ZTGK_ANIMATOR_H
#define ZTGK_ANIMATOR_H

#include "Animation.h"
#include <glm/glm.hpp>

class Animator
{
public:
    Animator(Animation* animation);

    void UpdateAnimation(float dt);

    void PlayAnimation(Animation* pAnimation);

    void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);

    std::vector<glm::mat4> GetFinalBoneMatrices();

private:
    std::vector<glm::mat4> m_FinalBoneMatrices;
    Animation* m_CurrentAnimation;
    float m_CurrentTime;
    float m_DeltaTime;
};


#endif //ZTGK_ANIMATOR_H
