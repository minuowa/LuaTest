#include "stdafx.h"
#include "LuaObjectManager.h"
#include "Component.h"
#include "Function.h"
namespace Lua {

LuaObjectManager::LuaObjectManager() {

}

LuaObjectManager::~LuaObjectManager() {
    this->Destroy();
}

void LuaObjectManager::Add(Component* com) {
    //assert(std::find(components_.front(), components_.end(), (const Component*&)com) == nullptr);
    components_.push_back(com);
}

void LuaObjectManager::Remove(Component* com) {
    components_.remove(com);
}

void LuaObjectManager::Destroy() {
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
