#include "stdafx.h"
#include "LuaTable.h"
#include "Function.h"
namespace Lua {
LuaTable::LuaTable(lua_State* state, int reference)
    : BaseValue( state, reference ) {
}

LuaTable::~LuaTable() {
}

Ptr<LuaTable> LuaTable::Create(lua_State* state) {
    lua_newtable(state);
    int ref = luaL_ref(state, LUA_REGISTRYINDEX);
    LuaTable* ret = new LuaTable(state, ref);
    return ret;
}

void LuaTable::SetValue(const char* key, Ptr<LuaTable> value) {
    this->_clear();
    this->_pushself();
    this->_pushvalue(value);
    this->_setkeyvalue(key);
}

void LuaTable::Print(const char* tag/*=nullptr*/) {
    this->_clear();
    this->_pushself();
    luaL_checktype(state_, 1, LUA_TTABLE);
    lua_pushnil(state_);
    while (lua_next(state_, 1)) {
        string key = LuaToString(state_, -2);
        string value = LuaToString(state_, -1);
        if (tag)
            printf("<%s> [%s] =%s\n", tag, key.c_str(), value.c_str());
        else
            printf("[%s] =%s\n", key.c_str(), value.c_str());
        lua_pop(state_, 1);
    }
}

void LuaTable::SetMetatable(Ptr<LuaTable> meta) {
    this->_clear();
    this->_pushself();
    this->_pushvalue(meta);
    this->_set_meta();
}


}

