//
// Created by cheily on 08.04.2024.
//

#pragma once


#include "ECS/System.h"
#include "Group.h"
#include "TextRenderer.h"
#include "SpriteRenderer.h"
#include "ECS/SignalQueue/SignalReceiver.h"

struct HUDRemapGroupsSignalData;

class HUD : public System {
public:
    std::unordered_map<unsigned, Group> groups;
    std::unique_ptr<TextRenderer> textRenderer;
    std::unique_ptr<SpriteRenderer> spriteRenderer;
    std::unique_ptr<SignalReceiver> signalReceiver;

    void draw();
    void drawGroup(unsigned groupID);
    Group * getDefaultGroup() const;
    Group * getGroupOrDefault(unsigned groupID) const;
    Group * getGroupOrAddDefault(unsigned groupID);
    unsigned addGroup(glm::vec3 offset = {0, 0, 0}, bool hidden = false);
    bool removeGroup(unsigned groupID);

    void init();
    void addComponent(void *component) override;
    void removeComponent(void *component) override;
    const std::type_index *getComponentTypes() override { return reinterpret_cast<const std::type_index *>(&componentTypes); }
    int getNumComponentTypes() override { return 2; }
    void showImGuiDetailsImpl(Camera *camera) override;

    std::unordered_map<unsigned, std::vector<Sprite*>> sprites;
    std::unordered_map<unsigned, std::vector<Text*>> texts;

    void sort_z();
    void remap_groups(HUDRemapGroupsSignalData data);

private:
    std::vector<Group *> z_sorted_groups;
    std::array<std::type_index, 2> componentTypes = {
        std::type_index(typeid(Sprite)),
        std::type_index(typeid(Text))
    };
};
