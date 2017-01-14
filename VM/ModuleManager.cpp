#include "stdafx.h"
#include "ModuleManager.h"
#include "VirtualMachine.h"
#include "LuaComponent.h"



ModuleManager::ModuleManager(VirtualMachine* owner)
    : virtual_machine_(owner) {

}

ModuleManager::~ModuleManager() {
    virtual_machine_ = nullptr;
}

Ptr<LuaTable> ModuleManager::CreateInstance(const char* moduleName) {
    LuaModule* module = nullptr;
    if (!dTryGetValue(modules_, moduleName, module)) {
        Ptr<LuaTable> luainstance = virtual_machine_->Require(moduleName);
        if (!luainstance.Valid())
            return nullptr;
        module = new LuaModule(moduleName, luainstance);
        modules_.insert(make_pair(moduleName, module));
    }

    auto instance = virtual_machine_->CreateTable();
    auto meta = virtual_machine_->CreateTable();
    meta->SetValue("__index", module->GetModuleTable());
    instance->SetMetatable(meta);
    return instance;
}

void ModuleManager::ReleaseInstance(LuaComponent* com) {
    if (!com)
        return;
    auto instance = com->GetLuaInstance();
    if (!instance.Valid())
        return;
    instance->SetMetatable(nullptr);
    LuaModule* module = nullptr;
    dTryGetValue(modules_, com->filename.c_str(), module);
    module->ReleaseInstance(instance);
}

void ModuleManager::Destroy() {
    dDeleteMap(modules_);
}
