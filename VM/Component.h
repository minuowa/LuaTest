#pragma once
#include "LuaTable.h"
namespace Lua {
class VirtualMachine;
class Component {
  public:
    Component();
    ~Component();
  public:
    VirtualMachine* virtual_machine;
  public:
    const Ptr<LuaTable>& GetLuaInstance() const;
    bool Initialize();
    virtual void Awake();
    virtual void Update();
    virtual void OnDestroy();
  public:
    string filename;
  private:
    Ptr<LuaTable> luainstance_;
};
}

