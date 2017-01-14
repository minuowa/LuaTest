#pragma once
#include "LuaTable.h"
class VirtualMachine;
class LuaComponent {
  public:
    LuaComponent();
    ~LuaComponent();
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

