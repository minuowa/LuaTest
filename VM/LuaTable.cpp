#include "stdafx.h"
#include "LuaTable.h"
LuaTable::LuaTable(lua_State* state, int reference)
	:LuaValue(state, reference)
{

}

LuaTable::~LuaTable()
{
}

void LuaTable::Print()
{

}
