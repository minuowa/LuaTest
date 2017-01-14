#pragma once
#include "LuaTable.h"
class LuaComponent {
  public:
    LuaComponent();
    ~LuaComponent();
  public:
    Ptr<LuaTable>& GetLuaInstance();
    bool Initialize();
    virtual void Awake();
    virtual void Update();
    virtual void OnDestroy();
  public:
    string filename;
  private:
    Ptr<LuaTable> luainstance_;
};

