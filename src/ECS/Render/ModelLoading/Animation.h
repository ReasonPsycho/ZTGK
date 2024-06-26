//
// Created by redkc on 09/06/2024.
//

#ifndef ZTGK_ANIMATION_H
#define ZTGK_ANIMATION_H


#include "glm/fwd.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "Model.h"
#include "Bone.h"
#include <string>
#include <vector>

struct AssimpNodeData
{
    glm::mat4 transformation;
    std::string name;
    int childrenCount;
    std::vector<AssimpNodeData> children;
};

class Animation
{
public:
    Animation() = default;

    Animation(const std::string& animationPath, Model* model);

    ~Animation();

    Bone* FindBone(const std::string& name);


    float GetTicksPerSecond();

    float GetDuration();

    const AssimpNodeData& GetRootNode();

    const std::map<std::string,BoneInfo>& GetBoneIDMap();
    glm::mat4 GetBoneTranslationMatrix(string name);
    int GetBoneIdFromName(string name);

private:
    void ReadMissingBones(const aiAnimation* animation, Model& model);

    void ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src);
    float m_Duration;
    int m_TicksPerSecond;
    std::vector<Bone> m_Bones;
    AssimpNodeData m_RootNode;
    std::map<std::string, BoneInfo> m_BoneInfoMap;
};


#endif //ZTGK_ANIMATION_H
