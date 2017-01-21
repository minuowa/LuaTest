#include "stdafx.h"
#include "VirtualMachine.h"
#include "Allocater.h"
#include "LuaTable.h"
#include <fstream>
#include "Fun.h"
#include <iostream>
namespace Lua {



VirtualMachine::VirtualMachine()
    : state_(nullptr)
    , allocater_(nullptr)
    , module_manager_(this) {
}


VirtualMachine::~VirtualMachine() {
    this->Close();
}


lua_State* VirtualMachine::GetState() {
    return state_;
}

VirtualFile* Lua::VirtualMachine::GetVirtualFile(const char* fileName) {
    auto ret = files_.find(fileName);
    if (ret != files_.end()) {
        return ret->second;
    }
    return nullptr;
}

void* GlobalAllocate(void *ud, void *ptr, size_t osize, size_t nsize) {
    VirtualMachine* vm = (VirtualMachine*)ud;
    return vm->Allocate(ptr, osize, nsize);
}

static int panic(lua_State *L) {
    (void)L; /* to avoid warnings */
    fprintf(stderr, "PANIC: unprotected error in call to Lua API (%s)\n",
            lua_tostring(L, -1));
    return 0;
}
bool VirtualMachine::Open() {
    allocater_ = new Allocater();
    if (!this->InitState()) {
        return false;
    }
    this->AddLoader();
    SnapGCObjects();
    allocater_->Snapshot();
    return true;
}

int Writer(lua_State *L, const void* p, size_t sz, void* ud) {
    return sz;
}
void VirtualMachine::Close() {
    if (state_ == nullptr) {
        return;
    }

    component_manager_.Destroy();
    module_manager_.Destroy();

    this->PrintDebugRegistry();
    this->GC();
    this->PrintGCCount("Close Lua");
    DumpGC(std::cout);
    //allocater_->DumpDifference(std::cout);
    lua_close(state_);
    state_ = nullptr;
    fun::delete_map_pointers(files_);
    SAFE_DELETE(allocater_);
}

void* VirtualMachine::Allocate(void *ptr, size_t osize, size_t nsize) {
    return allocater_->Allocate(ptr, osize, nsize);
}

void VirtualMachine::PrintGCCount(const char* what /*= nullptr*/) {
    if (what) {
        printf("%s>>GC Count(B):%d\n", what, GCBitCount());
    } else {
        printf(">>GC Count(B):%d\n", GCBitCount());
    }
}

void VirtualMachine::PrintError() const {
    const char* error = lua_tostring(state_, -1);
    printf("´íÎóÐÅÏ¢:%s\n", error);
    lua_pop(state_, 1);
}

void VirtualMachine::PrintSnapshot() const {
    int base = lua_gettop(state_);
    for (int i = base; i >= 0; --i) {
        printf("(%d)%s", i, LuaToString(state_, -1).c_str());
    }
}



void VirtualMachine::PrintDebugRegistry() const {
    const char* chunk = "\
	print(\"--------------------------------------\")\
	for k,v in pairs(debug.getregistry()) do\
		print('Registry:',k,v)\
	end\
	print(\"--------------------------------------\")\
                        ";
    this->DoString(chunk);
}

void VirtualMachine::PrintTop() const {
    printf("%s", LuaToString(state_, -1).c_str());
}


void VirtualMachine::PrintTable(const Pointer<LuaTable>& table, const char* tag/*=nullptr*/)const {
    if (table.Valid())
        table->Print(tag);
}

bool VirtualMachine::DoFile(const char* filename, const char* content/*= nullptr*/) {
    if (content != nullptr)
        this->TryAddFile(filename, content);

    if (luaL_dofile(state_, filename) != kRetSucess) {
        PrintError();
        return false;
    }
    return true;
}

Pointer<LuaTable> VirtualMachine::Require(const char* filename, const char* content/*= nullptr*/) {
    if (content != nullptr)
        this->TryAddFile(filename, content);

    string chunk;
    chunk += "require";
    chunk += " '";
    chunk += filename;
    chunk += "'";
    DoString(chunk.c_str());
    return this->GetGlobalTable(filename);
}

Pointer<LuaTable> VirtualMachine::GetGlobalTable(const char* name) {
    LuaTable* ret = nullptr;
    lua_getfield(state_, LUA_GLOBALSINDEX, name);
    if (lua_type(state_, -1) == LUA_TTABLE) {
        int ref = luaL_ref(state_, LUA_REGISTRYINDEX);
        ret = new LuaTable(state_, ref);
    }
    return ret;
}

Pointer<Function> VirtualMachine::GetFunction(const char* name) {
    Pointer<LuaTable> gtable = this->GetGlobalTable("_G");
    return gtable->GetFunction(name);
}

void VirtualMachine::UnloadModule(const char* moduleName) {
    string chunk;
    chunk += "package.loaded['";
    chunk += moduleName;
    chunk += "']=nil\n";

    chunk += "_G['";
    chunk += moduleName;
    chunk += "']=nil\n";

    DoString(chunk.c_str());
}

void VirtualMachine::Unref(int reference) {
    char buffer[250] = { 0, };
    sprintf_s(buffer, "debug.getregistry()[%d]=nil", reference);
    this->DoString(buffer);
    this->DoString("debug.getregistry()[0]=nil");
}

ModuleManager & VirtualMachine::GetModuleManager() {
    return module_manager_;
}

ComponentManager & VirtualMachine::GetComponentManager() {
    return component_manager_;
}

void VirtualMachine::SnapGCObjects() {
    list<void*> ret;
    list<void*> greys;
    list<void*> blacks;
    GCObject* node = state_->l_G->rootgc;
    while (node) {
        if (isblack(node))
            blacks.push_back(node);
        else if (isgray(node))
            greys.push_back(node);
        else if (iswhite(node))
            white_objects_.push_back(node);
        ret.push_back(node);
        node = node->gch.next;
    }
}
//#define LUA_TNIL		0
//#define LUA_TBOOLEAN		1
//#define LUA_TLIGHTUSERDATA	2
//#define LUA_TNUMBER		3
//#define LUA_TSTRING		4
//#define LUA_TTABLE		5
//#define LUA_TFUNCTION		6
//#define LUA_TUSERDATA		7
//#define LUA_TTHREAD		8
const char* names[] = {
    "Nil",
    "Bool",
    "LightUserdata",
    "Number",
    "String",
    "Table",
    "Fucntion",
    "Thread",
};

void VirtualMachine::DumpGC(ostream& stream /*= std::cout*/) {
    list<void*> curwhites;
    GCObject* node = state_->l_G->rootgc;
    while (node) {
        assert(iswhite(node));
        curwhites.push_back(node);
        node = node->gch.next;
    }
    //for (auto obj : white_objects_) {
    //    assert(std::find(curwhites.begin(), curwhites.end(), obj) != curwhites.end());
    //}
    char buffer[128] = { 0, };
    int count = 0;
    for (auto obj : curwhites) {
        if (std::find(white_objects_.begin(), white_objects_.end(), obj) == white_objects_.end()) {
            sprintf_s(buffer, "\nGCObject :0X%08X Type:%s", (unsigned int)obj, names[((GCObject*)obj)->gch.tt]);
            stream << buffer;
            count++;
        }
    }
    sprintf_s(buffer, "\nDump GC Object:%d (%d->%d)", count, white_objects_.size(), curwhites.size());
    stream << buffer;
}

bool VirtualMachine::InitState() {
    state_ = lua_newstate(GlobalAllocate, this);
    if (state_) {
        this->PrintGCCount("Open Lua");
        lua_atpanic(state_, &panic);
        luaL_openlibs(state_);
        this->ClearStack();
    }
    return state_ != nullptr;
}

void VirtualMachine::TryAddFile(const char* filename, const char* content) {
    VirtualFile* vf = GetVirtualFile(filename);
    if (!vf) {
        vf = new VirtualFile();
        vf->content = content;
        vf->filename = filename;
        files_.insert(make_pair(filename, vf));
    } else {
        vf->content = content;
    }
}


void VirtualMachine::ClearStack() {
    lua_pop(state_, lua_gettop(state_));
}

int VirtualMachine::GCBitCount() {
    return lua_gc(state_, LUA_GCCOUNTB, 0);
}

void VirtualMachine::GC() {
    lua_gc(state_, LUA_GCCOLLECT, 0);
}




bool VirtualMachine::DoString(const char* str, const char* chunkName /*= nullptr*/) const {
    if (luaL_loadbuffer(state_, str, strlen(str), chunkName) != kRetSucess) {
        PrintError();
        return false;
    }
    if (lua_pcall(state_, 0, LUA_MULTRET, 0) != kRetSucess) {
        PrintError();
        return false;
    }

    return true;
}

int VirtualMachine::MyLoader(lua_State * pState) {
    std::string module = lua_tostring(pState, 1);
    string fullname = module + ".lua";
    VirtualFile* file = getVirtualMachine(pState)->GetVirtualFile(module.c_str());

    if (file) {
        try {
            luaL_loadbuffer(pState, file->content.c_str(), file->content.length(), fullname.c_str());
        } catch (...) {
            std::string err = "\n\tError - MyLoader could not find ";
            err += module;
            err += ".";
            lua_pushstring(pState, err.c_str());
        }
    }
    return 1;
}

void VirtualMachine::AddLoader() {
    lua_getfield(state_, LUA_GLOBALSINDEX, "package");	// push "package"
    lua_getfield(state_, -1, "loaders");					// push "package.loaders"
    lua_remove(state_, -2);								// remove "package"
    // Count the number of entries in package.loaders.
    // Table is now at index -2, since 'nil' is right on top of it.
    // lua_next pushes a key and a value onto the stack.

    int numLoaders = 0;
    lua_pushnil(state_);

    while (lua_next(state_, -2) != 0) {
        lua_pop(state_, 1);
        numLoaders++;
    }

    lua_pushinteger(state_, numLoaders + 1);
    lua_pushcfunction(state_, MyLoader);
    lua_rawset(state_, -3);
    // Table is still on the stack.  Get rid of it now.

    lua_pop(state_, 1);
}
}