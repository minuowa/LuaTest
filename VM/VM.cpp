#include "stdafx.h"
#include "VM.h"
#include "Allocater.h"


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
	this->PrintGCCount();
	return true;
}


void VM::Close()
{
	if (mState == nullptr)
		return;

	this->PrintGCCount();
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
		printf("%s>>GC Count(B):%d", what, GCBitCount());
	else
		printf(">>GC Count(B):%d", GCBitCount());
}

void VM::PrintError()
{
	const char* error = lua_tostring(mState, -1);
	printf("¥ÌŒÛ–≈œ¢:%s\n", error);
	lua_pop(mState, 1);
}

bool VM::InitState()
{
	mState = lua_newstate(GlobalAllocate, this);
	if (mState)
	{
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
	if (luaL_dofile(mState, filename) != 0)
	{
		PrintError();
		return false;
	}
	return true;
}
