#include "stdafx.h"
#include "ComponentManager.h"
#include "Component.h"
#include "Function.h"
namespace Lua {

ComponentManager::ComponentManager() {

}

ComponentManager::~ComponentManager() {
    this->Destroy();
}

void ComponentManager::Add(Component* com) {
    //assert(std::find(components_.front(), components_.end(), (const Component*&)com) == nullptr);
    components_.push_back(com);
}

void ComponentManager::Remove(Component* com) {
    components_.remove(com);
}

void ComponentManager::Destroy() {
    if (components_.size() == 0)
        return;

    list<Component*> garbages;

    for (auto com : components_)
        garbages.push_back(com);

    for (auto com : garbages)
        com->OnDestroy();

    assert(components_.size() == 0);
}

}
