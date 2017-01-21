#pragma once
#include "Pointer.h"
#include "FunctionTaker.h"
namespace Lua {
class LuaTable;
class ModuleWrapper  {
  public:
    ModuleWrapper(const char* name, Pointer<LuaTable> luaValue);
    ~ModuleWrapper();
  public:
    const Pointer<LuaTable>& GetModuleTable() const;
    Pointer<LuaTable> CreateInstance();
    FunctionTaker* GetFunctionTaker();
    void ReleaseInstance(Pointer<LuaTable>& object);
  private:
    string name_;
    Pointer<LuaTable> module_table_;
    list<Pointer<LuaTable>> object_instances_;
    FunctionTaker function_taker_;
};
};

