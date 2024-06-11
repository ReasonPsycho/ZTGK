//
// Created by redkc on 09/06/2024.
//

#ifndef ZTGK_ASSIMPGLMHELPERS_H
#define ZTGK_ASSIMPGLMHELPERS_H


#include "glm/ext/matrix_float4x4.hpp"
#include "assimp/matrix4x4.h"
#include "glm/ext/quaternion_float.hpp"
#include "assimp/quaternion.h"

class AssimpGLMHelpers {
public:

    static  glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4& from);

    static glm::vec3 GetGLMVec(const aiVector3D& vec);

    static glm::quat GetGLMQuat(const aiQuaternion& pOrientation);
};



#endif //ZTGK_ASSIMPGLMHELPERS_H
