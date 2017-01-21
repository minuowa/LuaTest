#include "stdafx.h"
#include "ModuleWrapper.h"
#include "LuaTable.h"
#include "Function.h"

namespace Lua {

ModuleWrapper::ModuleWrapper(const char* name, Pointer<LuaTable> module_instance)
    : name_(name)
    , module_table_(module_instance) {
    function_taker_.Initialize(module_instance);
}

ModuleWrapper::~ModuleWrapper() {
    function_taker_.Destroy();
    assert(object_instances_.empty());
}

const Pointer<LuaTable>& ModuleWrapper::GetModuleTable()const {
    return module_table_;
}

Pointer<LuaTable> ModuleWrapper::CreateInstance() {
    auto ret = LuaTable::Create(module_table_->GetState());
    auto meta = LuaTable::Create(module_table_->GetState());
    meta->SetValue("__index", module_table_);
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
