//
// Created by redkc on 09/06/2024.
//

#include "Animation.h"

Animation::Animation(const string &animationPath, Model *model) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
    assert(scene && scene->mRootNode);
    auto animation = scene->mAnimations[0];
    m_Duration = animation->mDuration;
    m_TicksPerSecond = animation->mTicksPerSecond;
    ReadHeirarchyData(m_RootNode, scene->mRootNode);
    ReadMissingBones(animation, *model);
}

Bone *Animation::FindBone(const string &name) {
    auto iter = std::find_if(m_Bones.begin(), m_Bones.end(),
                             [&](const Bone& Bone)
                             {
                                 return Bone.GetBoneName() == name;
                             }
    );
    if (iter == m_Bones.end()) return nullptr;
    else return &(*iter);
}

float Animation::GetTicksPerSecond() { return m_TicksPerSecond; }

float Animation::GetDuration() { return m_Duration;}

const AssimpNodeData &Animation::GetRootNode() { return m_RootNode; }

const std::map<std::string, BoneInfo> &Animation::GetBoneIDMap() {
    return m_BoneInfoMap;
}

void Animation::ReadMissingBones(const aiAnimation *animation, Model &model) {
    int size = animation->mNumChannels;

    auto& boneInfoMap = model.GetBoneInfoMap();//getting m_BoneInfoMap from Model class
    int& boneCount = model.GetBoneCount(); //getting the m_BoneCounter from Model class

    //reading channels(bones engaged in an animation and their keyframes)
    for (int i = 0; i < size; i++)
    {
        auto channel = animation->mChannels[i];
        std::string boneName = channel->mNodeName.data;

        if (boneInfoMap.find(boneName) == boneInfoMap.end())
        {
            boneInfoMap[boneName].id = boneCount;
            boneCount++;
        }
        m_Bones.push_back(Bone(channel->mNodeName.data,
                               boneInfoMap[channel->mNodeName.data].id, channel));
    }

    m_BoneInfoMap = boneInfoMap;
}

void Animation::ReadHeirarchyData(AssimpNodeData &dest, const aiNode *src) {
    assert(src);

    dest.name = src->mName.data;
    dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
    dest.childrenCount = src->mNumChildren;

    for (int i = 0; i < src->mNumChildren; i++)
    {
        AssimpNodeData newData;
        ReadHeirarchyData(newData, src->mChildren[i]);
        dest.children.push_back(newData);
    }
}

Animation::~Animation() {
}

 glm::mat4 Animation::GetBoneTranslationMatrix(string name) {

    auto it = m_BoneInfoMap.find(name);
    std::vector<glm::mat4> boneTranslationPath;
    while(it != m_BoneInfoMap.end())
    {
        BoneInfo info = it->second;
        boneTranslationPath.push_back(info.offset);
        it = m_BoneInfoMap.find(info.parentNode);
    }
    glm::mat4 translationMatrix = glm::mat4(1);
    std::reverse(boneTranslationPath.begin(), boneTranslationPath.end());
    for (int i = 0; i < boneTranslationPath.size(); ++i) {
        translationMatrix *= boneTranslationPath[i];
    }
    return translationMatrix;
}

int Animation::GetBoneIdFromName(string name) {
    auto it = m_BoneInfoMap.find(name);
    if (it != m_BoneInfoMap.end()) {
        return it->second.id;
    } else {
        return -1;
    }
}
