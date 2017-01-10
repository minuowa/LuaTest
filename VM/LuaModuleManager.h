#pragma once
#include "LuaTable.h"
class LuaModuleManager
{
public:
	LuaModuleManager();
	~LuaModuleManager();
public:
	LuaTable* CreateInstance(const char* moduleName);
};

