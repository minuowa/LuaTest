#pragma once
#include "Ptr.h"
class LuaTable;
class LuaModule {
  public:
    LuaModule(const char* name, Ptr<LuaTable> luaValue);
    ~LuaModule();
  public:
    Ptr<LuaTable>& GetModuleTable();
    void ReleaseInstance(Ptr<LuaTable>& object);
  private:
    string name_;
    Ptr<LuaTable> module_table;
    list<Ptr<LuaTable>> object_instances_;
};

