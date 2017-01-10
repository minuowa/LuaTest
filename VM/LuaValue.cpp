#include "stdafx.h"
#include "LuaValue.h"


LuaValue::LuaValue(lua_State* state, int reference)
	:mReference(0)
	, mState(state)
	, mLuaReference(reference)
{

}

LuaValue::~LuaValue()
{
	assert(mReference == 0);
}

void LuaValue::GetField(const char* name)
{
	lua_getfield(mState, -1, name);
}

int LuaValue::GetReferenceCount()
{
	return mReference;
}

int LuaValue::DecReference()
{
	return --mReference;
}

int LuaValue::AddReference()
{
	return ++mReference;
}

void LuaValue::Push()
{
	lua_rawgeti(mState, LUA_REGISTRYINDEX, mLuaReference);
}

lua_Number LuaValue::GetNumber(const char* name)
{
	this->Push();
	this->GetField(name);
	assert(LUA_TNUMBER == lua_type(mState, -1));
	return lua_tonumber(mState, -1);
}

string LuaValue::GetString(const char* name)
{
	this->Push();
	this->GetField(name);
	assert(LUA_TSTRING == lua_type(mState, -1));
	return lua_tostring(mState, -1);
}
