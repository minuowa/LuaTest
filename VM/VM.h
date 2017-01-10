#pragma once
#include "LuaTable.h"
#include "Ptr.h"
class Allocater;

class VM
{
public: 
	static const int RetSucess = 0;
private: 
	lua_State* mState;
	Allocater* mAllocater;
	lua_Reader mLoader;
public:
	VM();
	~VM();
public:
	lua_State* GetState();

	bool Open();
	void Close();

	void GC();
	int GCBitCount();
	void* Allocate(void *ptr, size_t osize, size_t nsize);

	void SetLoader(lua_Reader loader);
	bool DoFile(const char* filename);
	bool DoString(const char* str);
	void PrintGCCount(const char* what = nullptr);
	void PrintError();

	Ptr<LuaTable> Require(string name);
	Ptr<LuaTable> GetTable(string name);
private:
	bool InitState();
};

