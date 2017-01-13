#include "stdafx.h"
#include "ModuleManager.h"
#include "VirtualMachine.h"



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

    return nullptr;
}
