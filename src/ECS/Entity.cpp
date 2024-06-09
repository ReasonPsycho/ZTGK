//
// Created by redkc on 10/01/2024.
//

#include "Entity.h"
#include "Utils/Util.h"
#include "tracy/Tracy.hpp"

using namespace ztgk;

Entity::Entity(Scene *scene, std::string name) : uniqueID(id<ID_POOL_ENTITY>()), scene(scene), name(name) {}

Entity::Entity(Scene *scene, Entity *parent, std::string name) : uniqueID(id<ID_POOL_ENTITY>()), scene(scene),
                                                                 parent(parent), name(name) {}


void Entity::forceUpdateSelfAndChild() {
    if (parent)
        transform.computeModelMatrix(parent->transform.getModelMatrix());
    else
        transform.computeModelMatrix();

    for (auto &pair: components) {
        pair.second->setIsDirty(true);
    }

    for (auto &&child: children) {
        child->forceUpdateSelfAndChild();
    }
}

void Entity::updateSelfAndChild() {
    if (transform.isDirty()) {
        forceUpdateSelfAndChild();
        return;
    } else {
        for (auto &pair: components) {
            pair.second->setIsDirty(false);
        }
    }

    if (updateChildren) {
        for (auto &&child: children) {
            child->updateSelfAndChild();
        }
    }

}

void Entity::removeComponentFromMap(Component * comp) {
    std::type_index typeName = std::type_index(typeid(*comp));
    scene->systemManager.removeComponent(comp);
    components.erase(typeName);
}

Entity *Entity::addChild(std::unique_ptr<Entity> child) {
    child->parent = this;
    children.push_back(std::move(child));
    return children.back().get();
}

void Entity::removeChild(Entity *child) {
    std::erase_if(children, [&](const std::unique_ptr<Entity> &e) { return e.get() == child; });
    removedChild = true;
}

void Entity::showImGuiDetails(Camera *camera) {
    ZoneTransientN(zoneName, (name).c_str(), true);
    Component *componentToDelete = nullptr;
    ImGui::PushID(uniqueID);
    ImGuiStorage *storage = ImGui::GetStateStorage();
    removedChild = false;

    if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_SpanAvailWidth)) {
        if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
            if (uniqueID != scene->selectedEntityNumber) {
                storage->SetBool(scene->selectedEntityNumber, false); // close the tree node
                scene->selectedEntityNumber = uniqueID;
                storage->SetBool(uniqueID, true); // close the tree node
            } else {
                storage->SetBool(scene->selectedEntityNumber, false); // close the tree node
                scene->selectedEntityNumber = -1;
            }

        }

        for (const auto &child: children) {
            child->showImGuiDetails(camera);
            if (removedChild) {
                break;
            }
        }
        if (scene->selectedEntityNumber == uniqueID) {
            ImVec2 window_pos = ImVec2(ImGui::GetIO().DisplaySize.x - 300, 40); // Top-Right
            ImGui::SetNextWindowPos(window_pos, ImGuiCond_FirstUseEver);
            ImGui::Begin((name + ", Element id:" + std::to_string(uniqueID) + "###Inspector").c_str(), nullptr, ImGuiWindowFlags_MenuBar);
            if (ImGui::BeginMenuBar()) {
                scene->systemManager.showImGuiEnitityBar(this);

                if (ImGui::MenuItem("Add child")) {
                    scene->addEntity(this,name + "Child");
                }
                if (ImGui::MenuItem("Update")) {

                    forceUpdateSelfAndChild();
                }
                
                ImGui::EndMenuBar();
            }

            transform.ManipulateModelMatrix(camera);
            if (!scene->stopRenderingImgui) {
                
                for (const auto &component: components) {
                    if (ImGui::CollapsingHeader(component.second->name.c_str())) {
                        ImGui::Indent();
                        component.second->showImGuiDetails(camera);
                        if (ImGui::Button("Delete component")) {
                            scene->stopRenderingImgui = true; //Just in case I am not sure if needed here.
                            removeComponentFromMap(component.second.get());
                            break;
                        }
                        ImGui::Unindent();
                    }
                }

                if (ImGui::Button("Delete entity")) {
                    Destroy();
                }
                 
            }
            ImGui::End();
        }
        ImGui::TreePop();
    }

    ImGui::PopID();
}

Entity::~Entity() {
    while (!components.empty()) {
        removeComponentFromMap(components.begin()->second.get());
    }
}

void Entity::Destroy() {
    while (!children.empty())
        (*children.begin())->Destroy();
    while (!components.empty())
        removeComponentFromMap(components.begin()->second.get());
    if (parent != nullptr) {
        parent->removeChild(this);
    } else {
        scene->removeChild(this);
    }
}

Entity *Entity::getChild(unsigned int id) const {
    auto found = std::find_if(children.begin(), children.end(), [id](auto & child){
        return child->uniqueID == id;
    });
    return found == children.end() ? nullptr : found->get();
}

Entity *Entity::getChild(const std::string &name) const {
    auto found = std::find_if(children.begin(), children.end(), [name](auto & child){
        return child->name == name;
    });
    return found == children.end() ? nullptr : found->get();
}

Entity *Entity::getChildR(unsigned int id) const {
    Entity * found = getChild(id);
    if (found != nullptr)
        return found;

    for (auto & child : children) {
        found = child->getChildR(id);
        if (found != nullptr)
            return found;
    }
    return nullptr;
}

Entity *Entity::getChildR(const string &name) const {
    Entity * found = getChild(name);
    if (found != nullptr)
        return found;

    for (auto & child : children) {
        found = child->getChildR(name);
        if (found != nullptr)
            return found;
    }
    return nullptr;
}

