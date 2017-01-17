#pragma once
#include "LuaTable.h"
#include "Pointer.h"
#include "LuaModule.h"
namespace Lua {
class VirtualMachine;
class Component;
class ModuleManager {
  public:
    ModuleManager(VirtualMachine* owner);
    ~ModuleManager();
  public:
    Pointer<LuaTable> CreateInstance(const char* moduleName);
    void ReleaseInstance(Component* com);
    void Destroy();
    LuaModule* Get(const char* name, bool require = true);
  private:
    VirtualMachine* virtual_machine_;
    map<string, LuaModule*> modules_;
};
};

