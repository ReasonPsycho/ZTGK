//
// Created by igork on 09.06.2024.
//

#include "MiningSystem.h"

void MiningSystem::addComponent(void *component) {
    if (auto *pranium = dynamic_cast<Pranium *>((IMineable *) component)) {
        praniumComponents.push_back(pranium);
    } else if (auto *mineableChest = dynamic_cast<MineableChest *>((IMineable *) component)) {
        mineableChestComponents.push_back(mineableChest);
    } else if(auto *mineable = dynamic_cast<IMineable *>((IMineable *) component)) {
        mineableComponents.push_back(mineable);
    }

}

void MiningSystem::removeComponent(void *component) {
    if (auto *pranium = dynamic_cast<Pranium *>((IMineable *) component)) {
        auto component_iter = std::find(praniumComponents.begin(), praniumComponents.end(), pranium);

        if (component_iter != praniumComponents.end()) {
            praniumComponents.erase(component_iter);
        }
    } else if (auto *mineableChest = dynamic_cast<MineableChest *>((IMineable *) component)) {
        auto component_iter = std::find(mineableChestComponents.begin(), mineableChestComponents.end(), mineableChest);

        if (component_iter != mineableChestComponents.end()) {
            mineableChestComponents.erase(component_iter);
        }
    } else if(auto *mineable = dynamic_cast<IMineable *>((IMineable *) component)) {
        auto component_iter = std::find(mineableComponents.begin(), mineableComponents.end(), mineable);

        if (component_iter != mineableComponents.end()) {
            mineableComponents.erase(component_iter);
        }
    }

}

const std::type_index *MiningSystem::getComponentTypes() {
    return componentTypes.data();
}

int MiningSystem::getNumComponentTypes() {
    return componentTypes.size();
}

void MiningSystem::registerComponents() {
}

void MiningSystem::showImGuiDetailsImpl(Camera *camera) {
    if (ImGui::CollapsingHeader(std::format("Pranium: {}###MiningSystem_Pranium", praniumComponents.size()).c_str())) {
        for (auto &pranium : praniumComponents) {
            if (ImGui::TreeNode(std::format("{} - id {}", pranium->name, pranium->uniqueID).c_str())) {
                pranium->showImGuiDetailsImpl(camera);
                ImGui::TreePop();
            }
        }
    }
    if (ImGui::CollapsingHeader(std::format("MineableChest: {}###MiningSystem_MineableChest", mineableChestComponents.size()).c_str())) {
        for (auto &mineableChest : mineableChestComponents) {
            if (ImGui::TreeNode(std::format("{} - id {}", mineableChest->name, mineableChest->uniqueID).c_str())) {
                mineableChest->showImGuiDetailsImpl(camera);
                ImGui::TreePop();
            }
        }
    }
    if (ImGui::CollapsingHeader(std::format("IMineable: {}###MiningSystem_IMineable", mineableComponents.size()).c_str())) {
        for (auto &mineable : mineableComponents) {
            if (ImGui::TreeNode(std::format("{} - id {}", mineable->name, mineable->uniqueID).c_str())) {
                mineable->showImGuiDetailsImpl(camera);
                ImGui::TreePop();
            }
        }
    }

}

void MiningSystem::UpdateImpl() {
    for (auto pranium : praniumComponents) {
        pranium->Update();
    }
    for (auto mineableChest : mineableChestComponents) {
        mineableChest->Update();
    }
//    for (auto mineable : mineableComponents) {
//        mineable->UpdateImpl();
//    }
}

MiningSystem::MiningSystem() {
    name = "MiningSystem";
}
