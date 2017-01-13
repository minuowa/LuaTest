#include "stdafx.h"
#include "LuaModule.h"



LuaModule::LuaModule(const char* name, Ptr<LuaTable> luaValue) 
	:mName(name)
	, mLuaValue(luaValue)
{

}

LuaModule::~LuaModule()
{
}
