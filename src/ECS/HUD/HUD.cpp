//
// Created by cheily on 08.04.2024.
//

#include "HUD.h"
#include "ECS/SignalQueue/Signal.h"
#include "ECS/SignalQueue/DataCargo/EditorSignals/HUD/HUDRemoveGroupSignalData.h"
#include "ECS/SignalQueue/DataCargo/EditorSignals/HUD/HUDRemapGroupsSignalData.h"
#include "ECS/SignalQueue/SignalQueue.h"
#include <ranges>
#include <algorithm>
using namespace std;

void HUD::init() {
    name = "HUD";

    auto g = Group::default_group();
    groups.insert({0, g});
    z_sorted_groups.push_back(&g);
    textRenderer = make_unique<TextRenderer>(this);
    spriteRenderer = make_unique<SpriteRenderer>(this);
    signalReceiver = make_unique<SignalReceiver>(Signal::signal_types.all_hud);
    signalReceiver->receive = [this](const Signal & signal) {
        if ( signal.stype == Signal::signal_types.hud_sort_z_depth_signal ) {
            sort_z();
            return;
        } else if ( signal.stype == Signal::signal_types.hud_remove_group_signal ) {
            removeGroup(std::dynamic_pointer_cast<HUDRemoveGroupSignalData>(signal.data)->groupID);
            return;
        } else if ( signal.stype == Signal::signal_types.hud_update_group_mappings_signal ) {
            remap_groups( *dynamic_pointer_cast<HUDRemapGroupsSignalData>(signal.data) );
            return;
        }
    };

    *ztgk::game::scene->systemManager.getSystem<SignalQueue>() += signalReceiver.get();
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
    std::erase_if(z_sorted_groups, [groupID](Group * g){ return g->id == groupID; });
    // Return value - The number of erased elements.
    return groups.erase(groupID) != 0;
}

void HUD::addComponent(void *component) {
    auto c = static_cast<AHUDComponent*>(component);
    switch (c->type) {
        case hudcType::UNDEFINED: {
            spdlog::error("Component type undefined! Cannot assign to HUD system.");
            break;
        }
        case hudcType::SPRITE: {
            Sprite * sprite = reinterpret_cast<Sprite*>(component);
            sprites[sprite->groupID].push_back(sprite);
            break;
        }
        case hudcType::TEXT: {
            Text * text = reinterpret_cast<Text*>(component);
            texts[text->groupID].push_back(text);
            break;
        }
    }
}

void HUD::removeComponent(void *component) {
    auto c = (AHUDComponent*)component;
    switch (c->type) {
        case hudcType::SPRITE: {
            erase(sprites[c->groupID], dynamic_cast<Sprite *>(c));
            break;
        }
        case hudcType::TEXT: {
            erase(texts[c->groupID], dynamic_cast<Text *>(c));
            break;
        }
    }
}

void HUD::showImGuiDetailsImpl(Camera *camera) {
    if (ImGui::Button("Sort Z Depth"))
        sort_z();
    ImGui::SameLine();
    if (ImGui::Button("Remap groups")) {
        remap_groups( HUDRemapGroupsSignalData() );
    }

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
    if (ImGui::CollapsingHeader("Managed Components")) {
        if (ImGui::TreeNodeEx("Sprites", ImGuiTreeNodeFlags_SpanAvailWidth)) {
            for (auto & pair : sprites) {
                for (auto & spr : sprites[pair.first]) {
                    if (ImGui::TreeNodeEx(std::format("ID {0}, '{1}'##Sprite{0}", spr->uniqueID, spr->editor_path).c_str(), ImGuiTreeNodeFlags_SpanAvailWidth)) {
                        spr->showImGuiDetailsImpl(camera);
                        ImGui::TreePop();
                    }
                }
            }
            ImGui::TreePop();
        }
        if (ImGui::TreeNodeEx("Texts", ImGuiTreeNodeFlags_SpanAvailWidth)) {
            for (auto & pair : texts) {
                for (auto & txt : texts[pair.first]) {
                    if (ImGui::TreeNodeEx(std::format("ID {0}, '{1}'##Text{0}", txt->uniqueID, txt->content).c_str(), ImGuiTreeNodeFlags_SpanAvailWidth)) {
                        txt->showImGuiDetailsImpl(camera);
                        ImGui::TreePop();
                    }
                }
            }
            ImGui::TreePop();
        }
    }
}

void HUD::sort_z() {
    std::sort(z_sorted_groups.begin(), z_sorted_groups.end(), [](Group * g1, Group * g2){ return g1->offset.z > g2->offset.z; });
}

void HUD::remap_groups(HUDRemapGroupsSignalData data) {
    if ( data.all ) {
        std::unordered_map<unsigned, std::vector<Sprite*>> remapped_s;
        for ( auto & mapping : sprites ) {
            for ( auto spr : mapping.second ) {
                remapped_s[spr->groupID].push_back(spr);
            }
        }
        std::unordered_map<unsigned, std::vector<Text*>> remapped_t;
        for ( auto & mapping : texts ) {
            for ( auto spr : mapping.second ) {
                remapped_t[spr->groupID].push_back(spr);
            }
        }
        sprites = remapped_s;
        texts = remapped_t;
    } else {
        switch (data.componentType) {
            case hudcType::SPRITE: {
                 auto pos = std::find_if(sprites[data.oldGroup].begin(), sprites[data.oldGroup].end(), [data](Sprite * spr){ return spr->uniqueID == data.componentID; });
                 auto e = sprites[data.oldGroup].end();
                 if ( pos == sprites[data.oldGroup].end() ) {
                     spdlog::warn("HUD group remap request - Component not found. Aborting.");
                     return;
                 }
                 if ( !groups.contains(data.newGroup) ) {
                     spdlog::warn("HUD group remap request - No such group pre-existing! Remap proceeding but element will not be accesible without a matching group element.");
                 }
                 auto val = *pos;
                 sprites[data.oldGroup].erase(pos);
                 sprites[data.newGroup].push_back(val);
                 return;
            }
            case hudcType::TEXT: {
                 auto pos = std::find_if(texts[data.oldGroup].begin(), texts[data.oldGroup].end(), [data](Text * spr){ return spr->uniqueID == data.componentID; });
                 if ( pos == texts[data.oldGroup].end() ) {
                     spdlog::warn("HUD group remap request - Component not found. Aborting.");
                     return;
                 }
                 if ( !groups.contains(data.newGroup) ) {
                     spdlog::warn("HUD group remap request - No such group pre-existing! Remap proceeding but element will not be accesible without a matching group element.");
                 }
                 auto val = *pos;
                 texts[data.oldGroup].erase(pos);
                 texts[data.newGroup].push_back(val);
                 return;
            }
            case hudcType::UNDEFINED: {
                spdlog::warn("HUD group remap request for undefined type! Aborting.");
                return;
            }
        }
    }
}
