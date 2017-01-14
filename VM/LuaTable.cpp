#include "stdafx.h"
#include "LuaTable.h"
LuaTable::LuaTable( lua_State* state, int reference )
    : LuaValue( state, reference ) {
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
    this->_pushself();
    this->_pushvalue(value);
    this->_setkeyvalue(key);
}

void LuaTable::Print() {
    this->_pushself();
    luaL_checktype(state_, 1, LUA_TTABLE);
    lua_pushnil(state_);
    while (lua_next(state_, 1)) {
        PrintLuaValue(state_, -1);
        PrintLuaValue(state_, -2);
        lua_pop(state_, 1);
    }
}

void LuaTable::SetMetatable(Ptr<LuaTable> meta) {
    this->_clear();
    this->_pushself();
    this->_pushvalue(meta);
    this->_set_meta();
}

