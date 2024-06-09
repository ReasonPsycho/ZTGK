//
// Created by redkc on 09/06/2024.
//

#ifndef ZTGK_ANIMATIONPLAYER_H
#define ZTGK_ANIMATIONPLAYER_H


#include "ECS/Component.h"
#include "ECS/Render/ModelLoading/Animator.h"
#include <map>
#include <string>

class AnimationPlayer: public Component {
public:
    AnimationPlayer();


    void UpdateImpl() override;
    void showImGuiDetailsImpl(Camera *camera) override;
    
private:
    Animator animator = nullptr;
    std::map<std::string, std::shared_ptr<Animation>> animationMap;
};


#endif //ZTGK_ANIMATIONPLAYER_H
