#pragma once
#include "Pointer.h"
#include "FunctionTaker.h"
namespace Lua {
class LuaTable;
class LuaModule;
class ModuleWrapper  {
  public:
    ModuleWrapper(const char* name, Pointer<LuaModule> luaValue);
    ~ModuleWrapper();
  public:
    const Pointer<LuaModule>& GetModule() const;
    Pointer<LuaTable> CreateInstance();
    FunctionTaker* GetFunctionTaker();
    void ReleaseInstance(Pointer<LuaTable>& object);
  private:
    string name_;
    Pointer<LuaModule> module_;
    list<Pointer<LuaTable>> object_instances_;
    FunctionTaker function_taker_;
};
};

