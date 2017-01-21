#pragma once
#include "LuaTable.h"
#include "Pointer.h"
#include "ModuleWrapper.h"
namespace Lua {
class VirtualMachine;
class Component;
class ModuleManager {
  public:
    ModuleManager(VirtualMachine* owner);
    ~ModuleManager();
  public:
    Pointer<LuaTable> CreateInstance(const char* modulename);
    FunctionTaker* GetFunctionTaker(const char* modulename);
    void ReleaseInstance(const char* modulename, Pointer<LuaTable> luaobject);
    void Destroy();
    ModuleWrapper* Get(const char* name, bool require = true);
  private:
    VirtualMachine* virtual_machine_;
    map<string, ModuleWrapper*> modules_;
};
};

