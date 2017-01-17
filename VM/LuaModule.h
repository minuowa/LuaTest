#pragma once
#include "Pointer.h"
namespace Lua {
class LuaTable;
class LuaModule {
  public:
    LuaModule(const char* name, Pointer<LuaTable> luaValue);
    ~LuaModule();
  public:
    const Pointer<LuaTable>& GetModuleTable() const;
    Pointer<LuaTable> CreateInstance();
    void ReleaseInstance(Pointer<LuaTable>& object);
  private:
    string name_;
    Pointer<LuaTable> module_table_;
    list<Pointer<LuaTable>> object_instances_;
};
};

