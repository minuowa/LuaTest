#pragma once
#include "LuaTable.h"
class LuaComponent
{
public:
    LuaComponent();
    ~LuaComponent();
public:
    string filename;
private:
    LuaTable* mInstance;
public:
    virtual void Awake();
    virtual void Update();
    virtual void OnDestroy();
};

