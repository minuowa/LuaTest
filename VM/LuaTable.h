#pragma once
#include "LuaValue.h"
class LuaTable :public LuaValue
{
public:
	LuaTable(lua_State* state, int reference);
	~LuaTable();
public:
	void Print();
public: 

};

