//
// Created by redkc on 09/06/2024.
//

#include "AnimationPlayer.h"

AnimationPlayer::AnimationPlayer() {
    name = "Animation Player";
}

void AnimationPlayer::UpdateImpl() {
    animator.UpdateAnimation((float )Time::Instance().DeltaTime());
    Render *render = getEntity()->getComponent<Render>();
    if (render != nullptr) {
        render->isAnimated = true;
        render->animationTransforms = animator.GetFinalBoneMatrices();
    }
}

void AnimationPlayer::showImGuiDetailsImpl(Camera *camera) {
    if (ImGui::Button("Play animation")) {
        PlayAnimation("res/models/gabka/pan_gabka_move.fbx");
    }
}

void AnimationPlayer::PlayAnimation(std::string path) {
    animator.PlayAnimation(animationMap[path]);
}
