//
// Created by redkc on 09/06/2024.
//

#ifndef ZTGK_ANIMATIONPLAYER_H
#define ZTGK_ANIMATIONPLAYER_H


#include "ECS/Component.h"
#include "ECS/Render/ModelLoading/Animator.h"
#include <map>
#include <string>
#include "ECS/Entity.h"
#include "ECS/Utils/Time.h"

class AnimationPlayer: public Component {
public:
    AnimationPlayer();

    void PlayAnimation(std::string path);
    
    void UpdateImpl() override;
    void showImGuiDetailsImpl(Camera *camera) override;

    std::map<std::string, Animation*> animationMap;
    
private:
    Animator animator = nullptr;
};


#endif //ZTGK_ANIMATIONPLAYER_H
