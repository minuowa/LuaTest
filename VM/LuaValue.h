#pragma once
class LuaValue
{
private:
	int mReference;
	int mLuaReference;
	lua_State* mState;
public:
	LuaValue(lua_State* state,int reference);
	~LuaValue();
protected:
	void GetField(const char* name);
	void Push();
public:
	int GetReferenceCount();
	int DecReference();
	int AddReference();
	lua_Number GetNumber(const char* name);
	string GetString(const char* name);
};

