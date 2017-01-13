#include "stdafx.h"
#include "LuaTable.h"
LuaTable::LuaTable( lua_State* state, int reference )
    : LuaValue( state, reference ) {

}

LuaTable::~LuaTable() {
}

void LuaTable::Print() {

}


void LuaTable::SetValue(const char* name, lua_Number value) {
    this->Push();
}

void LuaTable::SetValue(const char* name, const char* value) {

}

void LuaTable::SetValue(const char* name, Ptr<LuaTable> value) {

}

