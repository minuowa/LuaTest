#include "stdafx.h"
#include "VirtualMachine.h"
#include "Allocater.h"
#include "LuaTable.h"
#include <fstream>
#include "Fun.h"
#include <iostream>


map<string, VirtualFile*> VirtualMachine::files_;

VirtualMachine::VirtualMachine()
    : state_( nullptr )
    , allocater_( nullptr )
    , module_manager_( this ) {
    Instance = this;
}


VirtualMachine::~VirtualMachine() {
    this->Close();
}

lua_State* VirtualMachine::GetState() {
    return state_;
}

VirtualFile* VirtualMachine::GetVirtualFile( const char* fileName ) {
    auto ret = files_.find( fileName );
    if ( ret != files_.end() ) {
        return ret->second;
    }
    return nullptr;
}

void* GlobalAllocate( void *ud, void *ptr, size_t osize, size_t nsize ) {
    VirtualMachine* vm = ( VirtualMachine* )ud;
    return vm->Allocate( ptr, osize, nsize );
}

static int panic( lua_State *L ) {
    ( void )L; /* to avoid warnings */
    fprintf( stderr, "PANIC: unprotected error in call to Lua API (%s)\n",
             lua_tostring( L, -1 ) );
    return 0;
}
bool VirtualMachine::Open() {
    allocater_ = new Allocater();
    if ( !this->InitState() ) {
        return false;
    }
    this->AddLoader();
    return true;
}


void VirtualMachine::Close() {
    if ( state_ == nullptr ) {
        return;
    }
    this->GC();
    this->PrintGCCount( "Close Lua" );
    lua_close( state_ );
    state_ = nullptr;
    dDeleteMap( files_ );
    SAFE_DELETE( allocater_ );
}

void* VirtualMachine::Allocate( void *ptr, size_t osize, size_t nsize ) {
    return allocater_->Allocate( ptr, osize, nsize );
}

void VirtualMachine::PrintGCCount( const char* what /*= nullptr*/ ) {
    if ( what ) {
        printf( "%s>>GC Count(B):%d\n", what, GCBitCount() );
    } else {
        printf( ">>GC Count(B):%d\n", GCBitCount() );
    }
}

void VirtualMachine::PrintError() {
    const char* error = lua_tostring( state_, -1 );
    printf( "´íÎóÐÅÏ¢:%s\n", error );
    lua_pop( state_, 1 );
}

void VirtualMachine::PrintSnapshot() {
    int base = lua_gettop(state_);
    for (int i = base; i >= 0; --i) {
        PrintLuaValue(state_, i);
    }
}



void VirtualMachine::PrintTop() {
    PrintLuaValue(state_, -1);
}

Ptr<LuaTable> VirtualMachine::Require(string name) {
    string cmd;
    cmd += "require";
    cmd += " '";
    cmd += name;
    cmd += "'";
    DoString( cmd.c_str() );
    return this->GetTable( name );
}

Ptr<LuaTable> VirtualMachine::Require( const char* str, const char* moduleName ) {
    VirtualFile* vf = GetVirtualFile( moduleName );
    if ( !vf ) {
        vf = new VirtualFile();
        vf->content = str;
        vf->modulename = moduleName;
        files_.insert( make_pair( moduleName, vf ) );
    } else {
        vf->content = str;
    }

    Ptr<LuaTable> m = Require( moduleName );
    return m;
}

Ptr<LuaTable> VirtualMachine::GetTable( string name ) {
    LuaTable* ret = nullptr;
    lua_getfield( state_, LUA_GLOBALSINDEX, name.c_str() );
    if ( lua_type( state_, -1 ) == LUA_TTABLE ) {
        int ref = luaL_ref( state_, LUA_REGISTRYINDEX );
        ret = new LuaTable( state_, ref );
    }
    return ret;
}

Ptr<LuaTable> VirtualMachine::CreateTable() {
    lua_newtable( state_ );
    int ref = luaL_ref( state_, LUA_REGISTRYINDEX );
    LuaTable* ret = new LuaTable( state_, ref );
    return ret;
}

void VirtualMachine::UnloadModule(const char* moduleName) {
    string cmd;
    cmd += "package.loaded['";
    cmd += moduleName;
    cmd += "']=nil\n";

    cmd += "_G['";
    cmd += moduleName;
    cmd += "']=nil\n";

    DoString(cmd.c_str());

    cmd.clear();
}

ModuleManager& VirtualMachine::GetModuleManager() {
    return module_manager_;
}

bool VirtualMachine::InitState() {
    state_ = lua_newstate( GlobalAllocate, this );
    if ( state_ ) {
        this->PrintGCCount( "Open Lua" );
        lua_atpanic( state_, &panic );
        luaL_openlibs( state_ );
        lua_pop(state_, 1);
    }
    return state_ != nullptr;
}

VirtualMachine* VirtualMachine::Instance = nullptr;

int VirtualMachine::GCBitCount() {
    return lua_gc( state_, LUA_GCCOUNTB, 0 );
}

void VirtualMachine::GC() {
    lua_gc( state_, LUA_GCCOLLECT, 0 );
}

bool VirtualMachine::DoFile( const char* filename ) {
    if ( luaL_dofile( state_, filename ) != kRetSucess ) {
        PrintError();
        return false;
    }
    return true;
}

bool VirtualMachine::DoString( const char* str, const char* chunkName /*= nullptr*/ ) {
    if( luaL_loadbuffer( state_, str, strlen( str ), chunkName ) != kRetSucess ) {
        PrintError();
        return false;
    }
    if ( lua_pcall( state_, 0, LUA_MULTRET, 0 ) != kRetSucess ) {
        PrintError();
        return false;
    }

    return true;
}

int VirtualMachine::MyLoader( lua_State* pState ) {
    std::string module = lua_tostring( pState, 1 );
    string fullname = module + ".lua";
    VirtualFile* file = GetVirtualFile( module.c_str() );

    if( file ) {
        try {
            luaL_loadbuffer( pState, file->content.c_str(), file->content.length(), fullname.c_str() );
        } catch ( ... ) {
            std::string err = "\n\tError - MyLoader could not find ";
            err += module;
            err += ".";
            lua_pushstring( pState, err.c_str() );
        }
    }
    return 1;
}

void VirtualMachine::AddLoader() {
    lua_getfield( state_, LUA_GLOBALSINDEX, "package" );	// push "package"
    lua_getfield( state_, -1, "loaders" );					// push "package.loaders"
    lua_remove( state_, -2 );								// remove "package"
    // Count the number of entries in package.loaders.
    // Table is now at index -2, since 'nil' is right on top of it.
    // lua_next pushes a key and a value onto the stack.

    int numLoaders = 0;
    lua_pushnil( state_ );

    while ( lua_next( state_, -2 ) != 0 ) {
        lua_pop( state_, 1 );
        numLoaders++;
    }

    lua_pushinteger( state_, numLoaders + 1 );
    lua_pushcfunction( state_, MyLoader );
    lua_rawset( state_, -3 );
    // Table is still on the stack.  Get rid of it now.

    lua_pop( state_, 1 );
}
