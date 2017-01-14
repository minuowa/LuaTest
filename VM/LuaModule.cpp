#include "stdafx.h"
#include "LuaModule.h"
#include "LuaTable.h"



LuaModule::LuaModule(const char* name, Ptr<LuaTable> module_instance)
    : name_(name)
    , module_table(module_instance) {

}

LuaModule::~LuaModule() {
    module_table->DecReference();
}

Ptr<LuaTable>& LuaModule::GetModuleTable() {
    return module_table;
}

void LuaModule::ReleaseInstance(Ptr<LuaTable>& object) {
    object_instances_.remove(object);
    //module_table->DecReference();
}
