#pragma once
#include "LuaTable.h"
#include "Ptr.h"
#include "LuaModule.h"
class VirtualMachine;
class LuaComponent;
class ModuleManager {
  public:
    ModuleManager(VirtualMachine* owner);
    ~ModuleManager();
  public:
    Ptr<LuaTable> CreateInstance(const char* moduleName);
    void ReleaseInstance(LuaComponent* com);
    void Destroy();
    LuaModule* Get(const char* name, bool require = true);
  private:
    VirtualMachine* virtual_machine_;
    map<string, LuaModule*> modules_;
};

