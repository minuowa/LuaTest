#pragma once
#include "LuaTable.h"
#include "Ptr.h"
#include "VirtualFile.h"
#include "ModuleManager.h"
class Allocater;

class VirtualMachine {
  public:
    VirtualMachine();
    ~VirtualMachine();
  public:
    lua_State* GetState();
    static VirtualFile* GetVirtualFile( const char* fileName );
    static int MyLoader( lua_State * pState );

    bool Open();
    void Close();

    void GC();
    int GCBitCount();
    void* Allocate( void *ptr, size_t osize, size_t nsize );

    void AddLoader();
    void PrintGCCount( const char* what = nullptr );
    void PrintError();

    bool DoFile( const char* filename );
    bool DoString( const char* str, const char* chunkName = nullptr );

    Ptr<LuaTable> Require( const char* str, const char* moduleName );
    Ptr<LuaTable> Require( string name );
    Ptr<LuaTable> GetTable( string name );
    Ptr<LuaTable> CreateTable();
    void SetMetatable(Ptr<LuaTable> a, Ptr<LuaTable> b);
    void SetTopValue(const char* key, lua_Number value, int index = -2);
    void SetTopValue(const char* key, const char* value, int index = -2);
    void SetTopValue(const char* key, Ptr<LuaTable> value, int index = -2);

    ModuleManager& GetModuleManager();
  private:
    bool InitState();

  public:
    const string FileExtension = ".lua";
    static const int kRetSucess = 0;
  private:
    lua_State* state_;
    Allocater* allocater_;
    ModuleManager module_manager_;
    static map<string, VirtualFile*> files_;
};

