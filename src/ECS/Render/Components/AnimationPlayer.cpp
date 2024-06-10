// 
// Created by redkc on 09/06/2024. 
// 
 
#include "AnimationPlayer.h" 
 
AnimationPlayer::AnimationPlayer() { 
    name = "Animation Player"; 
} 
 
void AnimationPlayer::UpdateImpl() { 
    if(isPlaying){ 
        animator.UpdateAnimation((float )Time::Instance().DeltaTime() * animationSpeed); 
        Render *render = getEntity()->getComponent<Render>(); 
        if (render != nullptr) { 
            render->isAnimated = true; 
            render->animationTransforms = animator.GetFinalBoneMatrices(); 
        } 
        if (!looping && animator.m_CurrentAnimation->GetDuration() < animator.m_CurrentTime){ 
            isPlaying = false; 
            looping = false; 
            animationSpeed = 1.0f; 
        } 
    } 
} 
 
void AnimationPlayer::showImGuiDetailsImpl(Camera *camera) { 
// Use a vector to store the keys 
    std::vector<const char*> keys; 
    for (const auto& kv : animationMap) 
    { 
        keys.push_back(kv.first.c_str()); 
    } 
 
// Create the combo 
    static int selectedItem = -1; 
    ImGui::Combo("Animation", &selectedItem, keys.data(), keys.size());  
     
    ImGui::Checkbox("Looping",&looping); 
    ImGui::InputFloat("Animation speed",&animationSpeed); 
     
    if (ImGui::Button("Play animation")) { 
        PlayAnimation(keys[selectedItem], looping, animationSpeed); 
    } 
} 
 
void AnimationPlayer::PlayAnimation(std::string path, bool looping, float animationSpeed) { 
    isPlaying = true; 
    animator.PlayAnimation(animationMap[path]); 
    this->looping = looping; 
    this->animationSpeed = animationSpeed; 
} 
 
void AnimationPlayer::StopAnimation() { 
    isPlaying = false; 
    looping = false; 
    animationSpeed = 1.0f; 
} 
