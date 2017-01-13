#pragma once
#include "LuaTable.h"
#include "Ptr.h"
#include "VirtualFile.h"
class Allocater;

class VM
{
public: 
	const string FileExtension = ".lua";
	static const int RetSucess = 0;
private: 
	lua_State* mState;
	Allocater* mAllocater;
	static map<string, VirtualFile*> mFiles;
public:
	VM();
	~VM();
public:
	lua_State* GetState();
public:
	static VirtualFile* GetVirtualFile(const char* fileName);
	static int MyLoader(lua_State * pState);

	bool Open();
	void Close();

	void GC();
	int GCBitCount();
	void* Allocate(void *ptr, size_t osize, size_t nsize);

	void AddLoader();
	void PrintGCCount(const char* what = nullptr);
	void PrintError();

	bool DoFile(const char* filename);
	bool DoString(const char* str, const char* chunkName = nullptr);

	Ptr<LuaTable> Require(const char* str, const char* moduleName);
	Ptr<LuaTable> Require(string name);
	Ptr<LuaTable> GetTable(string name);
private:
	bool InitState();
};

