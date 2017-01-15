#pragma once
#include "Ptr.h"
namespace Lua {
class LuaTable;
class LuaModule {
  public:
    LuaModule(const char* name, Ptr<LuaTable> luaValue);
    ~LuaModule();
  public:
    const Ptr<LuaTable>& GetModuleTable() const;
    Ptr<LuaTable> CreateInstance();
    void ReleaseInstance(Ptr<LuaTable>& object);
  private:
    string name_;
    Ptr<LuaTable> module_table_;
    list<Ptr<LuaTable>> object_instances_;
};
};

