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

Pointer<LuaTable> ModuleManager::CreateInstance(const char* moduleName) {
    ModuleWrapper* module = this->Get(moduleName);
    return module ? module->CreateInstance() : nullptr;
}


FunctionTaker* ModuleManager::GetFunctionTaker(const char* moduleName) {
    ModuleWrapper* module = this->Get(moduleName);
    if (module)
        return module->GetFunctionTaker();
    return nullptr;
}

void ModuleManager::ReleaseInstance(const char* modulename, Pointer<LuaTable> luaobject) {
    assert(luaobject.Valid());
    luaobject->SetMetatable(nullptr);
    ModuleWrapper* module = nullptr;
    fun::try_get_map_value(modules_, modulename, module);
    module->ReleaseInstance(luaobject);
}

void ModuleManager::Destroy() {
    fun::delete_map_pointers(modules_);
}

ModuleWrapper* ModuleManager::Get(const char* name, bool require /*= true*/) {
    ModuleWrapper* module = nullptr;
    if (!fun::try_get_map_value(modules_, name, module) && require) {
        Pointer<LuaTable> luainstance = virtual_machine_->Require(name);
        if (!luainstance.Valid())
            return nullptr;
        module = new ModuleWrapper(name, luainstance);
        modules_.insert(make_pair(name, module));
    }
    return module;
}
}
