#include "stdafx.h"
#include "ModuleWrapper.h"
#include "LuaTable.h"
#include "Function.h"
#include "LuaModule.h"

namespace Lua {

ModuleWrapper::ModuleWrapper(const char* name, Pointer<LuaModule> module_instance)
    : name_(name)
    , module_(module_instance) {
    function_taker_.Initialize(module_instance);
}

ModuleWrapper::~ModuleWrapper() {
    function_taker_.Destroy();
    assert(object_instances_.empty());
}

const Pointer<LuaModule>& ModuleWrapper::GetModule()const {
    return module_;
}

Pointer<LuaTable> ModuleWrapper::CreateInstance() {
    auto ret = LuaTable::Create(module_->GetState());
    auto meta = LuaTable::Create(module_->GetState());
    meta->SetValue("__index", module_);
    ret->SetMetatable(meta);
    object_instances_.push_back(ret);
    return ret;
}

FunctionTaker* ModuleWrapper::GetFunctionTaker() {
    return &function_taker_;
}

void ModuleWrapper::ReleaseInstance(Pointer<LuaTable>& object) {
    object_instances_.remove(object);
}
}
