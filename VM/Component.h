#pragma once
#include "LuaTable.h"
namespace Lua {
class VirtualMachine;
class FunctionTaker;
class Component {
  public:
    Component();
    ~Component();
  public:
    VirtualMachine* virtual_machine;
    FunctionTaker* function_taker;
  public:
    const Pointer<LuaTable>& GetLuaInstance() const;
    bool Initialize();
    virtual void Awake();
    virtual void Update();
    virtual void OnDestroy();
  public:
    string filename;
  private:
    Pointer<LuaTable> luainstance_;
};
}

