#pragma once
#include "LuaTable.h"
#include "Ptr.h"
#include "LuaModule.h"
class VirtualMachine;
class ModuleManager {
  public:
    ModuleManager(VirtualMachine* owner);
    ~ModuleManager();
  private:
    VirtualMachine* virtual_machine_;
    map<string, LuaModule*> modules_;
  public:
    Ptr<LuaTable> CreateInstance(const char* moduleName);
};

