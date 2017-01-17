#pragma once
#include "BaseValue.h"
#include "Pointer.h"
namespace Lua {
class LuaTable : public BaseValue {
  public:
    typedef BaseValue base;
  public:
    LuaTable(lua_State* state, int reference);
    ~LuaTable();
  public:
    static Pointer<LuaTable> Create(lua_State* state);

    void SetValue(const char* key, Pointer<LuaTable> value);
    template<typename T> void SetValue(const char* key, T value) {
        this->_pushself();
        this->_pushvalue(value);
        this->_setkeyvalue(key);
        this->_clear();
    }
    virtual void Print(const char* tag = nullptr)override;
    void SetMetatable(Pointer<LuaTable> meta);
};
}

