#pragma once
#include "Pointer.h"
#include "PointerBase.h"

namespace Lua {
class LuaTable;
class LuaModule;
class Function;

class BaseValue : public PointerBase {
  public:
    BaseValue(lua_State* state, int reference);
    virtual ~BaseValue();
  public:
    lua_State* GetState() const;

    void PrintAddress();
    virtual void Print(const char* tag = nullptr);
    lua_Number GetNumber(const char* key);
    string GetString(const char* key);

    Pointer<Function> GetFunction(const char* name);
  protected:
    void _setkeyvalue(const char* key);
    void _pushself();
    void _getkey(const char* name);
    void _pushvalue(const char* value);
    void _pushvalue(lua_Number value);
    void _pushvalue(Pointer<LuaTable> value);
    void _pushvalue(Pointer<LuaModule> value);
    void _clear();
    void _set_meta();
    void _call(int argcount, int retcount);
    int _type();

    Pointer<LuaTable> _return_table();
    Pointer<Function> _return_function();
    const char* _return_str();
    lua_Number _return_number();

    template<typename T = void> T _return() {
        return (T)_return_number();
    }

    template<> const char* _return() {
        return _return_str();
    }

    template<> Pointer<LuaTable> _return() {
        return _return_table();
    };

    template<> Pointer<Function> _return() {
        return _return_function();
    };

    template<> void _return() {
    }

  protected:
    lua_State* state_;
  private:
    int lua_reference_;
    static int stack_count_;
};
};


