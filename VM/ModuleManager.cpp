#include "stdafx.h"
#include "ModuleManager.h"
#include "VirtualMachine.h"
#include "Component.h"

namespace Lua {
ModuleManager::ModuleManager(VirtualMachine* owner)
    : virtual_machine_(owner) {

}

ModuleManager::~ModuleManager() {
    virtual_machine_ = nullptr;
}

Ptr<LuaTable> ModuleManager::CreateInstance(const char* moduleName) {
    LuaModule* module = this->Get(moduleName);
    return module ? module->CreateInstance() : nullptr;
}

void ModuleManager::ReleaseInstance(Component* com) {
    if (com == nullptr)
        return;
    auto instance = com->GetLuaInstance();
    assert(instance.Valid());
    instance->SetMetatable(nullptr);
    LuaModule* module = nullptr;
    fun::try_get_map_value(modules_, com->filename.c_str(), module);
    module->ReleaseInstance(instance);
}

void ModuleManager::Destroy() {
    fun::delete_map_pointers(modules_);
}

LuaModule* ModuleManager::Get(const char* name, bool require /*= true*/) {
    LuaModule* module = nullptr;
    if (!fun::try_get_map_value(modules_, name, module) && require) {
        Ptr<LuaTable> luainstance = virtual_machine_->Require(name);
        if (!luainstance.Valid())
            return nullptr;
        module = new LuaModule(name, luainstance);
        modules_.insert(make_pair(name, module));
    }
    return module;
}
}
