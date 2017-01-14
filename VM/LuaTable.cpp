#include "stdafx.h"
#include "LuaTable.h"
LuaTable::LuaTable( lua_State* state, int reference )
    : LuaValue( state, reference ) {
}

LuaTable::~LuaTable() {
}



void LuaTable::SetValue(const char* key, Ptr<LuaTable> value) {
    this->_pushthis();
    this->_pushvalue(value);
    this->_setkeyvalue(key);
}

void LuaTable::SetMetatable(Ptr<LuaTable> meta) {
    this->_pushthis();
    this->_pushvalue(meta);
    this->_set_meta();
}

