#include "stdafx.h"
#include "LuaModule.h"
#include "Function.h"
#include "VirtualMachine.h"

namespace Lua {

const char* ModuleReferenceKey = "__ref";

LuaModule::LuaModule(lua_State* state, int reference, const char* name)
    : LuaTable(state, reference)
    , name_(name) {
    int modulereference = GetModuleReferenceCount();
    SetModuleReferenceCount(modulereference + 1);
}

LuaModule::~LuaModule() {
    int modulereference = GetModuleReferenceCount();
    modulereference--;
    if (modulereference == 0) {
        VirtualMachine* vm = getVirtualMachine(state_);
        vm->UnloadModule(name_.c_str());
    } else {
        SetModuleReferenceCount(modulereference);
    }
}

int LuaModule::GetModuleReferenceCount() {
    return (int)GetNumber(ModuleReferenceKey);
}

void LuaModule::SetModuleReferenceCount(int count) {
    this->SetValue(ModuleReferenceKey, count);
}

}
