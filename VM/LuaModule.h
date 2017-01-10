#pragma once
#include "LuaTable.h"
class LuaModule
{
public:
	LuaModule();
	~LuaModule();
private:
	LuaTable* mLuaValue;
};

