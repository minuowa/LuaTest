#include "stdafx.h"
#include "VM.h"
#include "Allocater.h"
#include "LuaTable.h"
#include <fstream>
#include "Delete.h"


map<string, VirtualFile*> VM::mFiles;

VM::VM()
	:mState(nullptr)
	, mAllocater(nullptr)
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

VirtualFile* VM::GetVirtualFile(const char* fileName)
{
	auto ret = mFiles.find(fileName);
	if (ret != mFiles.end())
		return ret->second;
	return nullptr;
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
	this->AddLoader();
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
	DeleteMap(mFiles);
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
	VirtualFile* vf = GetVirtualFile(moduleName);
	if (!vf)
	{
		vf = new VirtualFile();
		vf->content = str;
		vf->modulename = moduleName;
		mFiles.insert(make_pair(moduleName, vf));
	}
	else
	{
		vf->content = str;
	}

	Ptr<LuaTable> m = Require(moduleName);
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

int VM::MyLoader(lua_State* pState)
{
	std::string module = lua_tostring(pState, 1);
	string fullname = module + ".lua";
	VirtualFile* file = GetVirtualFile(module.c_str());

	if(file)
	{
		luaL_loadbuffer(pState, file->content.c_str(), file->content.length(), fullname.c_str());
	}
	else
	{
		try
		{
			ifstream in(fullname);
			size_t size = in.tellg();
			in.seekg(0, ios::beg);
			char* buffer = new char[size];
			in.read(buffer, size);
			in.close();
			luaL_loadbuffer(pState, buffer, size, fullname.c_str());
		}
		catch (...)
		{
			std::string err = "\n\tError - MyLoader could not find ";
			err += module;
			err += ".";
			lua_pushstring(pState, err.c_str());
		}
	}
	return 1;
}

void VM::AddLoader()
{
	lua_getfield(mState, LUA_GLOBALSINDEX, "package");	// push "package"
	lua_getfield(mState, -1, "loaders");					// push "package.loaders"
	lua_remove(mState, -2);								// remove "package"
															// Count the number of entries in package.loaders.
															// Table is now at index -2, since 'nil' is right on top of it.
															// lua_next pushes a key and a value onto the stack.

	int numLoaders = 0;
	lua_pushnil(mState);

	while (lua_next(mState, -2) != 0)
	{
		lua_pop(mState, 1);
		numLoaders++;
	}

	lua_pushinteger(mState, numLoaders + 1);
	lua_pushcfunction(mState, MyLoader);
	lua_rawset(mState, -3);
	// Table is still on the stack.  Get rid of it now.

	lua_pop(mState, 1);
}
