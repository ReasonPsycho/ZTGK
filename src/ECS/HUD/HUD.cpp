//
// Created by cheily on 08.04.2024.
//

#include "HUD.h"
#include <ranges>
#include <algorithm>
using namespace std;

void HUD::init() {
    name = "HUD";
    // []op auto adds default group
    z_sorted_groups.push_back(&groups[0]);
    textRenderer = make_unique<TextRenderer>(this);
    spriteRenderer = make_unique<SpriteRenderer>(this);
}

void HUD::draw() {
    for (auto pair : z_sorted_groups | std::views::filter([](Group * g){ return !g->hidden; })) {
        drawGroup(pair->id);
    }
}

void HUD::drawGroup(unsigned int groupID) {
    if ( !groups.contains(groupID) ) {
        spdlog::warn(std::format("HUD Group {} not found! Defaulting to group 0.", groupID));
        groupID = 0;
    }
    for ( auto sprite : sprites[groupID] ) {
        spriteRenderer->render(sprite);
    }
    for ( auto text : texts[groupID] ) {
        textRenderer->render(text);
    }
}

Group *HUD::getDefaultGroup() const {
    return const_cast<Group *>(&groups.at(0));
}

Group *HUD::getGroupOrDefault(unsigned groupID) const {
    if ( !groups.contains(groupID) ) {
        spdlog::warn(std::format("No HUD group {} found! Using default group.", groupID));
        return getDefaultGroup();
    }
    return const_cast<Group *>(&groups.at(groupID));
}

Group *HUD::getGroupOrAddDefault(unsigned int groupID) {
    return &groups[groupID];
}

unsigned HUD::addGroup(glm::vec3 offset, bool hidden) {
    Group newGroup;
    newGroup.offset = offset;
    newGroup.setHidden(hidden);
    groups.insert({newGroup.id, newGroup});
    z_sorted_groups.push_back(&groups.at(newGroup.id));
    sort_z();
    return newGroup.id;
}

bool HUD::removeGroup(unsigned int groupID) {
    // Return value - The number of erased elements.
    std::erase_if(z_sorted_groups, [groupID](Group * g){ return g->id == groupID; });
    return groups.erase(groupID) != 0;
}

void HUD::addComponent(void *component) {
    auto c = static_cast<AHUDComponent*>(component);
    switch (c->type) {
        case AHUDComponent::SPRITE: {
            Sprite * sprite = reinterpret_cast<Sprite*>(component);
            sprites[sprite->groupID].push_back(sprite);
            break;
        }
        case AHUDComponent::TEXT: {
            Text * text = reinterpret_cast<Text*>(component);
            texts[text->groupID].push_back(text);
            break;
        }
    }
}

void HUD::removeComponent(void *component) {
    auto c = (AHUDComponent*)component;
    switch (c->type) {
        case AHUDComponent::SPRITE: {
            erase(sprites[c->groupID], dynamic_cast<Sprite *>(c));
            break;
        }
        case AHUDComponent::TEXT: {
            erase(texts[c->groupID], dynamic_cast<Text *>(c));
            break;
        }
    }
}

void HUD::showImGuiDetails(Camera *camera) {
    if (ImGui::Button("Sort"))
        sort_z();
    if (ImGui::CollapsingHeader("Groups", true)) {
        if (ImGui::Button("New Group"))
            addGroup();
        for (auto & group: groups)
            group.second.imgui_controls();
    }
    if (ImGui::CollapsingHeader("Sprite Renderer"))
        spriteRenderer->imgui_controls();
    if (ImGui::CollapsingHeader("Text Renderer"))
        textRenderer->imgui_controls();
}

void HUD::sort_z() {
    std::sort(z_sorted_groups.begin(), z_sorted_groups.end(), [](Group * g1, Group * g2){ return g1->offset.z > g2->offset.z; });
}
