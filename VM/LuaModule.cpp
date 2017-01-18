#include "stdafx.h"
#include "LuaModule.h"
#include "LuaTable.h"
#include "Function.h"

namespace Lua {

LuaModule::LuaModule(const char* name, Pointer<LuaTable> module_instance)
    : name_(name)
    , module_table_(module_instance) {
    function_taker_.Initialize(module_instance);
}

LuaModule::~LuaModule() {
    function_taker_.Destroy();
    assert(object_instances_.empty());
}

const Pointer<LuaTable>& LuaModule::GetModuleTable()const {
    return module_table_;
}

Pointer<LuaTable> LuaModule::CreateInstance() {
    auto ret = LuaTable::Create(module_table_->GetState());
    auto meta = LuaTable::Create(module_table_->GetState());
    meta->SetValue("__index", module_table_);
    ret->SetMetatable(meta);
    object_instances_.push_back(ret);
    return ret;
}

FunctionTaker* LuaModule::GetFunctionTaker() {
    return &function_taker_;
}

void LuaModule::ReleaseInstance(Pointer<LuaTable>& object) {
    object_instances_.remove(object);
}
}
