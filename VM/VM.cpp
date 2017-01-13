#include "stdafx.h"
#include "VM.h"
#include "Allocater.h"
#include "LuaTable.h"
#include <fstream>


VM::VM()
	:mState(nullptr)
	, mAllocater(nullptr)
	, mLoader(nullptr)
{
}


VM::~VM()
{
	this->Close();
}

lua_State* VM::GetState()
{
	return mState;
}

void VM::SetLoader(lua_Reader loader)
{
	mLoader = loader;
}

void* GlobalAllocate(void *ud, void *ptr, size_t osize, size_t nsize)
{
	VM* vm = (VM*)ud;

	return vm->Allocate(ptr, osize, nsize);
}

static int panic(lua_State *L) {
	(void)L;  /* to avoid warnings */
	fprintf(stderr, "PANIC: unprotected error in call to Lua API (%s)\n",
		lua_tostring(L, -1));
	return 0;
}
bool VM::Open()
{
	mAllocater = new Allocater();
	if (!this->InitState())
		return false;
	return true;
}


void VM::Close()
{
	if (mState == nullptr)
		return;
	this->GC();
	this->PrintGCCount("Close Lua");
	lua_close(mState);
	mState = nullptr;
	SAFE_DELETE(mAllocater);
}

void* VM::Allocate(void *ptr, size_t osize, size_t nsize)
{
	return mAllocater->Allocate(ptr, osize, nsize);
}

void VM::PrintGCCount(const char* what /*= nullptr*/)
{
	if (what)
		printf("%s>>GC Count(B):%d\n", what, GCBitCount());
	else
		printf(">>GC Count(B):%d\n", GCBitCount());
}

void VM::PrintError()
{
	const char* error = lua_tostring(mState, -1);
	printf("¥ÌŒÛ–≈œ¢:%s\n", error);
	lua_pop(mState, 1);
}

Ptr<LuaTable> VM::Require(string name)
{
	string cmd;
	cmd += "require";
	cmd += " '";
	cmd += name;
	cmd += "'";
	DoString(cmd.c_str());
	return this->GetTable(name);
}

Ptr<LuaTable> VM::Require(const char* str, const char* moduleName)
{
	if (!str || !moduleName)
		return nullptr;

	string filename = moduleName;
	if (string::npos == filename.find(FileExtension))
		filename += FileExtension;

	std::ofstream of(filename);
	of << str;
	of.close();

	Ptr<LuaTable> m = Require(moduleName);
	remove(filename.c_str());
	return m;
}

Ptr<LuaTable> VM::GetTable(string name)
{
	LuaTable* ret = nullptr;
	lua_getfield(mState, LUA_GLOBALSINDEX, name.c_str());
	if (lua_type(mState, -1) == LUA_TTABLE)
	{
		int ref = luaL_ref(mState, LUA_REGISTRYINDEX);
		ret = new LuaTable(mState, ref);
	}
	return Ptr<LuaTable>(ret);
}

bool VM::InitState()
{
	mState = lua_newstate(GlobalAllocate, this);
	if (mState)
	{
		this->PrintGCCount("Open Lua");
		lua_atpanic(mState, &panic);
		luaL_openlibs(mState);
	}
	return mState != nullptr;
}

int VM::GCBitCount()
{
	return lua_gc(mState, LUA_GCCOUNTB, 0);
}

void VM::GC()
{
	lua_gc(mState, LUA_GCCOLLECT, 0);
}

bool VM::DoFile(const char* filename)
{
	if (luaL_dofile(mState, filename) != RetSucess)
	{
		PrintError();
		return false;
	}
	return true;
}

bool VM::DoString(const char* str, const char* chunkName /*= nullptr*/)
{
	if( luaL_loadbuffer(mState, str, strlen(str), chunkName) != RetSucess)
	{
		PrintError();
		return false;
	}
	if (lua_pcall(mState, 0, LUA_MULTRET, 0) != RetSucess)
	{
		PrintError();
		return false;
	}
	
	return true;
}
