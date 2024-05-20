//
// Created by cheily on 08.04.2024.
//

#include "HUD.h"
#include "ECS/Entity.h"
#include "ECS/SignalQueue/Signal.h"
#include "ECS/SignalQueue/DataCargo/EditorSignals/HUD/HUDRemoveGroupSignalData.h"
#include "ECS/SignalQueue/DataCargo/EditorSignals/HUD/HUDRemapGroupsSignalData.h"
#include "ECS/SignalQueue/DataCargo/MouseEvents/MouseButtonSignalData.h"
#include "ECS/SignalQueue/SignalQueue.h"
#include "Components/HudCompType.h"
#include "ECS/SignalQueue/DataCargo/MouseEvents/MouseMoveSignalData.h"
#include <ranges>
#include <algorithm>
using namespace std;

void HUD::init() {
    name = "HUD";

    auto g = Group::default_group();
    groups.insert({0, g});
    z_sorted_groups.push_back(&groups.at(0));
    textRenderer = make_unique<TextRenderer>(this);
    spriteRenderer = make_unique<SpriteRenderer>(this);
    signalReceiver = make_unique<SignalReceiver>(Signal::signal_types.all_hud | Signal::signal_types.mouse_move_signal | Signal::signal_types.mouse_button_signal);
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
        } else if ( signal.stype == Signal::signal_types.mouse_move_signal ) {
            auto data = dynamic_pointer_cast<MouseMoveSignalData>(signal.data);
            static HUDHoverable * hovered = nullptr;

            // for each non-hidden group, in order of z-index...
            for (auto & group : z_sorted_groups
            | std::views::filter([this](Group * g){ return !isGroupTreeHidden(g->id); })
            | std::views::reverse) {
                // go through each hoverable belonging to the group...
                for (auto & hoverable : hoverables[group->id]) {
                    // and if the mouse is within the hoverable...
                    if (spriteRenderer->bounds(hoverable->collisionSprite).contains(data->pos)) {
                        // and the hoverable was not hovered on before...
                        if (hoverable != hovered) {
                            // quit the old hoverable (if possible) and enter the new one
                            if (hovered != nullptr)
                                hovered->onHoverExit(hovered);

                            hovered = hoverable;
                            hovered->onHoverEnter(hovered);
                        }
                        return;
                    }
                }
            }
            // if no element is hovered upon, clear the old hover
            if (hovered != nullptr && !spriteRenderer->bounds(hovered->collisionSprite).contains(data->pos)) {
                hovered->onHoverExit(hovered);
                hovered = nullptr;
            }
        } else if ( signal.stype == Signal::signal_types.mouse_button_signal ) {
            auto data = dynamic_pointer_cast<MouseButtonSignalData>(signal.data);
            // for each non-hidden group, in order of z-index...
            // reverse
            for (auto & group : z_sorted_groups
            | std::views::filter([this](Group * g){ return !isGroupTreeHidden(g->id); })
            | std::views::reverse) {
                // go through each button belonging to the group...
                for (auto & button : buttons[group->id]) {
                    // and if the mouse is within the button...
                    if (spriteRenderer->bounds(button->collisionSprite).contains(data->pos)) {
                        // and the button was pressed...
                        if (data->action == GLFW_PRESS) {
                            button->onPress(button);
                        }
                        // and the button was released...
                        if (data->action == GLFW_RELEASE) {
                            button->onRelease(button);
                        }
                        return;
                    }
                }
            }
        }
    };

    *ztgk::game::scene->systemManager.getSystem<SignalQueue>() += signalReceiver.get();
}

void HUD::draw() {
    // no reverse
    //  same layer -> draw older elements first (in bg)
    //  diff layer -> as per sort_z
    for (auto pair : z_sorted_groups
    | std::views::filter([this](Group * g){ return !isGroupTreeHidden(g->id); })) {
        drawGroup(pair->id);
    }
}

void HUD::drawGroup(unsigned int groupID) {
    if ( !groups.contains(groupID) ) {
        spdlog::warn(std::format("HUD Group {} not found! Defaulting to groupID 0.", groupID));
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
        spdlog::warn(std::format("No HUD groupID {} found! Using default groupID.", groupID));
        return getDefaultGroup();
    }
    return const_cast<Group *>(&groups.at(groupID));
}

Group *HUD::getGroupOrAddDefault(unsigned int groupID) {
    return &groups[groupID];
}

unsigned int HUD::addGroup(unsigned int parentGroupID, const string &name, bool hidden, glm::vec3 offset) {
    Group newGroup;
    newGroup.offset = offset;
    newGroup.setHidden(hidden);
    newGroup.name = name;
    newGroup.parent = parentGroupID;
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

std::vector<AHUDComponent *> HUD::getOfGroup(unsigned int groupID) {
    std::vector<AHUDComponent *> ret;
    ret.append_range(texts[groupID]);
    ret.append_range(sprites[groupID]);
    return ret;
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
            Text * text = reinterpret_cast<Text *>(component);
            texts[text->groupID].push_back(text);
            break;
        }
        case hudcType::HOVERABLE: {
            HUDHoverable * hoverable = reinterpret_cast<HUDHoverable*>(component);
            hoverables[hoverable->groupID].push_back(hoverable);
            break;
        }
        case hudcType::BUTTON: {
            HUDButton * button = reinterpret_cast<HUDButton*>(component);
            buttons[button->groupID].push_back(button);
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
        case hudcType::HOVERABLE: {
            erase(hoverables[c->groupID], dynamic_cast<HUDHoverable *>(c));
            break;
        }
        case hudcType::BUTTON: {
            erase(buttons[c->groupID], dynamic_cast<HUDButton *>(c));
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
        if (ImGui::TreeNodeEx("Hoverables", ImGuiTreeNodeFlags_SpanAvailWidth)) {
            for (auto & pair : hoverables) {
                for (auto & hov : hoverables[pair.first]) {
                    if (ImGui::TreeNodeEx(std::format("ID {0}##Hoverable{0}", hov->uniqueID).c_str(), ImGuiTreeNodeFlags_SpanAvailWidth)) {
                        hov->showImGuiDetailsImpl(camera);
                        ImGui::TreePop();
                    }
                }
            }
            ImGui::TreePop();
        }
        if (ImGui::TreeNodeEx("Buttons", ImGuiTreeNodeFlags_SpanAvailWidth)) {
            for (auto & pair : buttons) {
                for (auto & btn : buttons[pair.first]) {
                    if (ImGui::TreeNodeEx(std::format("ID {0}##Button{0}", btn->uniqueID).c_str(), ImGuiTreeNodeFlags_SpanAvailWidth)) {
                        btn->showImGuiDetailsImpl(camera);
                        ImGui::TreePop();
                    }
                }
            }
            ImGui::TreePop();
        }
    }
}

// this ordering is aligned with draw order -> higher z draws first so in the background
// to have proper event handling, the sorted collection needs to be reversed -> newer (more in fg) elems handle first
void HUD::sort_z() {
    std::sort(z_sorted_groups.begin(), z_sorted_groups.end(), [this](Group * g1, Group * g2){ return getGroupTreeOffset(g1->id).z > getGroupTreeOffset(g2->id).z; });
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
            for ( auto txt : mapping.second ) {
                remapped_t[txt->groupID].push_back(txt);
            }
        }
        std::unordered_map<unsigned, std::vector<HUDHoverable*>> remapped_h;
        for ( auto & mapping : hoverables ) {
            for ( auto hov : mapping.second ) {
                remapped_h[hov->groupID].push_back(hov);
            }
        }
        std::unordered_map<unsigned, std::vector<HUDButton*>> remapped_b;
        for ( auto & mapping : buttons ) {
            for ( auto btn : mapping.second ) {
                remapped_b[btn->groupID].push_back(btn);
            }
        }
        sprites = remapped_s;
        texts = remapped_t;
        hoverables = remapped_h;
        buttons = remapped_b;
    } else {
        switch (data.componentType) {
            case hudcType::SPRITE: {
                 auto pos = std::find_if(sprites[data.oldGroup].begin(), sprites[data.oldGroup].end(), [data](Sprite * spr){ return spr->uniqueID == data.componentID; });
                 if ( pos == sprites[data.oldGroup].end() ) {
                     spdlog::warn("HUD groupID remap request - Component not found. Aborting.");
                     return;
                 }
                 if ( !groups.contains(data.newGroup) ) {
                     spdlog::warn("HUD groupID remap request - No such groupID pre-existing! Remap proceeding but element will not be accesible without a matching groupID element.");
                 }
                 auto val = *pos;
                 sprites[data.oldGroup].erase(pos);
                 sprites[data.newGroup].push_back(val);
                 return;
            }
            case hudcType::TEXT: {
                 auto pos = std::find_if(texts[data.oldGroup].begin(), texts[data.oldGroup].end(), [data](Text * spr){ return spr->uniqueID == data.componentID; });
                 if ( pos == texts[data.oldGroup].end() ) {
                     spdlog::warn("HUD groupID remap request - Component not found. Aborting.");
                     return;
                 }
                 if ( !groups.contains(data.newGroup) ) {
                     spdlog::warn("HUD groupID remap request - No such groupID pre-existing! Remap proceeding but element will not be accesible without a matching groupID element.");
                 }
                 auto val = *pos;
                 texts[data.oldGroup].erase(pos);
                 texts[data.newGroup].push_back(val);
                 return;
            }
            case hudcType::HOVERABLE: {
                 auto pos = std::find_if(hoverables[data.oldGroup].begin(), hoverables[data.oldGroup].end(), [data](HUDHoverable * spr){ return spr->uniqueID == data.componentID; });
                 if ( pos == hoverables[data.oldGroup].end() ) {
                     spdlog::warn("HUD groupID remap request - Component not found. Aborting.");
                     return;
                 }
                 if ( !groups.contains(data.newGroup) ) {
                     spdlog::warn("HUD groupID remap request - No such groupID pre-existing! Remap proceeding but element will not be accesible without a matching groupID element.");
                 }
                 auto val = *pos;
                 hoverables[data.oldGroup].erase(pos);
                 hoverables[data.newGroup].push_back(val);
                 return;
            }
            case hudcType::BUTTON: {
                 auto pos = std::find_if(buttons[data.oldGroup].begin(), buttons[data.oldGroup].end(), [data](HUDButton * spr){ return spr->uniqueID == data.componentID; });
                 if ( pos == buttons[data.oldGroup].end() ) {
                     spdlog::warn("HUD groupID remap request - Component not found. Aborting.");
                     return;
                 }
                 if ( !groups.contains(data.newGroup) ) {
                     spdlog::warn("HUD groupID remap request - No such groupID pre-existing! Remap proceeding but element will not be accesible without a matching groupID element.");
                 }
                 auto val = *pos;
                 buttons[data.oldGroup].erase(pos);
                 buttons[data.newGroup].push_back(val);
                 return;
            }
            case hudcType::UNDEFINED: {
                spdlog::warn("HUD groupID remap request for undefined type! Aborting.");
                return;
            }
        }
    }
}

glm::vec3 HUD::getGroupTreeOffset(unsigned int leafGroupID) const {
    if ( !groups.contains(leafGroupID) ) {
        spdlog::warn(std::format("HUD::getGroupTreeOffset:: No HUD groupID {} found!", leafGroupID));
        return {};
    }
    Group * group = getGroupOrDefault(leafGroupID);
    glm::vec3 offset = group->offset;
    while (group->parent != static_cast<unsigned>(-1)) {    // should only be -1 for root
        if (group->parent == group->id) {
            spdlog::warn("Group {} has itself as parent! Aborting.", group->id);
            return offset;
        }
        // get groupID first to handle root offset correctly
        group = getGroupOrDefault(group->parent);
        offset += group->offset;
    }
    return offset;
}

bool HUD::isGroupTreeHidden(unsigned int leafGroupID) const {
    if ( !groups.contains(leafGroupID) ) {
        spdlog::warn(std::format("HUD::isGroupTreeHidden:: No HUD groupID {} found!", leafGroupID));
        return true;
    }
    Group * group = getGroupOrDefault(leafGroupID);
    if (group->hidden)
        return true;
    while (group->parent != static_cast<unsigned>(-1)) {
        if (group->parent == group->id) {
            spdlog::warn("Group {} has itself as parent! Aborting.", group->id);
            return true;
        }
        group = getGroupOrDefault(group->parent);
        if (group->hidden)
            return true;
    }
    return false;
}

Group *HUD::findGroupByName(const string &name) const {
    for (auto & pair : groups) {
        if (pair.second.name == name)
            return const_cast<Group *>(&pair.second);
    }
    return getDefaultGroup();
}



#pragma region Element Creation

Entity *HUD::createButton(const std::string &text, glm::vec2 centerPos, glm::vec2 size, glm::vec4 defaultColor,
                          HUDHoverable::hover_func onHoverEnter, HUDHoverable::hover_func onHoverExit,
                          HUDButton::button_func onPress, HUDButton::button_func onRelease, Entity *parent,
                          unsigned int parentGroupID) {
    Entity * entity;
    if (parent)
        entity = ztgk::game::scene->addEntity(parent, "Button - " + text);
    else entity = ztgk::game::scene->addEntity("Button - " + text);
    auto group = addGroup(parentGroupID, "Button - " + text);
    entity->addComponent(std::make_unique<Sprite>(centerPos, size, defaultColor, group));
    auto spr = entity->getComponent<Sprite>();
    spr->mode = CENTER;
    entity->addComponent(std::make_unique<Text>(text, centerPos, glm::vec2(1, 1), ztgk::color.WHITE, ztgk::font.default_font, NONE, group));
    auto txt = entity->getComponent<Text>();
    txt->mode = CENTER;
    auto txt_size = textRenderer->size(txt);
    glm::vec2 new_scale = glm::vec2(0.9, 0.8) * spr->size / txt_size.total;
    txt->scale = new_scale;
    entity->addComponent(std::make_unique<HUDHoverable>(
        entity->getComponent<Sprite>(), group,
        std::move(onHoverEnter), std::move(onHoverExit)
    ));
    entity->addComponent(std::make_unique<HUDButton>(
        entity->getComponent<Sprite>(), group,
        std::move(onPress), std::move(onRelease)
    ));

    return entity;
}

Entity *HUD::createButton(glm::vec2 centerPos, glm::vec2 size, const std::string &foregroundSpritePath,
                          const std::string &backgroundSpritePath, const std::function<void()> &onRelease,
                          Entity *parent,
                          unsigned int parentGroupID) {
    Entity * entity;
    auto fgname = foregroundSpritePath.substr(foregroundSpritePath.find_last_of('/'));
    auto bgname = backgroundSpritePath.substr(backgroundSpritePath.find_last_of('/'));
    if (parent)
        entity = ztgk::game::scene->addEntity(parent, "Button FG: " + fgname + "; BG: " + bgname);
    else entity = ztgk::game::scene->addEntity("Button FG: " + fgname + "; BG: " + bgname);
    auto group = addGroup(parentGroupID, "Button FG: " + fgname + "; BG: " + bgname);

    auto bgent = ztgk::game::scene->addEntity(entity, "Background");
    bgent->addComponent(std::make_unique<Sprite>(centerPos, size, ztgk::color.WHITE, group, backgroundSpritePath));
    auto bgspr = bgent->getComponent<Sprite>();
    bgspr->mode = CENTER;

    entity->addComponent(std::make_unique<Sprite>(centerPos, size, ztgk::color.WHITE, group, foregroundSpritePath));
    auto spr = entity->getComponent<Sprite>();
    spr->mode = CENTER;

    static glm::vec4 color = ztgk::color.WHITE;
    static glm::vec4 hoverColor = ztgk::color.WHITE * glm::vec4{0.9, 0.9, 0.9, 1};
    static glm::vec4 pressColor = ztgk::color.WHITE * glm::vec4{0.8f, 0.8f, 0.8f, 1};

    entity->addComponent(std::make_unique<HUDHoverable>(bgspr, group,
        [spr](HUDHoverable * self) {
            spr->color = hoverColor;
        },
        [spr](HUDHoverable * self) {
            spr->color = color;
        }
    ));
    entity->addComponent(std::make_unique<HUDButton>(bgspr, group,
        [spr](HUDButton * self) {
            spr->color = pressColor;
        },
        [spr, onRelease](HUDButton * self) {
            onRelease();
            spr->color = hoverColor;
        }
    ));

    return entity;
}

Entity *
HUD::createButton(const std::string &text, glm::vec2 centerPos, glm::vec2 size, glm::vec4 color, glm::vec4 hoverColor,
                  glm::vec4 pressColor, const std::function<void()> &onRelease, Entity *parent,
                  unsigned int parentGroupID) {
    Entity * entity;
    if (parent)
        entity = ztgk::game::scene->addEntity(parent, "Button - " + text);
    else entity = ztgk::game::scene->addEntity("Button - " + text);
    auto group = addGroup(parentGroupID, "Button - " + text);
    entity->addComponent(std::make_unique<Sprite>(centerPos, size, color, group));
    auto spr = entity->getComponent<Sprite>();
    spr->mode = CENTER;
    entity->addComponent(std::make_unique<Text>(text, centerPos, glm::vec2(1, 1), ztgk::color.WHITE, ztgk::font.default_font, NONE, group));
    auto txt = entity->getComponent<Text>();
    txt->mode = CENTER;
    auto txt_size = textRenderer->size(txt);
    glm::vec2 new_scale = glm::vec2(0.9, 0.8) * spr->size / txt_size.total;
    txt->scale = new_scale;
    entity->addComponent(std::make_unique<HUDHoverable>(entity->getComponent<Sprite>(), group,
        [hoverColor](HUDHoverable * self) {
            self->collisionSprite->color = hoverColor;
            self->collisionSprite->load();
        },
        [color](HUDHoverable * self) {
            self->collisionSprite->color = color;
            self->collisionSprite->load();
        }
    ));
    entity->addComponent(std::make_unique<HUDButton>(entity->getComponent<Sprite>(), group,
        [pressColor](HUDButton * self) {
            self->collisionSprite->color = pressColor;
            self->collisionSprite->load();
        },
        [onRelease, hoverColor](HUDButton * self) {
            onRelease();
            self->collisionSprite->color = hoverColor;
            self->collisionSprite->load();
        }
    ));

    return entity;
}

#pragma endregion
