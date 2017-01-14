#include "stdafx.h"
#include "LuaModule.h"
#include "LuaTable.h"



LuaModule::LuaModule(const char* name, Ptr<LuaTable> module_instance)
    : name_(name)
    , module_table_(module_instance) {
}

LuaModule::~LuaModule() {
    assert(object_instances_.empty());
}

const Ptr<LuaTable>& LuaModule::GetModuleTable()const {
    return module_table_;
}

Ptr<LuaTable> LuaModule::CreateInstance() {
    auto ret = LuaTable::Create(module_table_->GetState());
    auto meta = LuaTable::Create(module_table_->GetState());
    meta->SetValue("__index", module_table_);
    ret->SetMetatable(meta);
    object_instances_.push_back(ret);
    return ret;
}

void LuaModule::ReleaseInstance(Ptr<LuaTable>& object) {
    object_instances_.remove(object);
}
