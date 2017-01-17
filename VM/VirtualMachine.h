#pragma once
#include "LuaTable.h"
#include "Ptr.h"
#include "VirtualFile.h"
#include "ModuleManager.h"
#include "Component.h"
#include "Function.h"

namespace Lua {
class Allocater;
class VirtualMachine {
  public:
    VirtualMachine();
    ~VirtualMachine();
  public:
    lua_State* GetState();
    static VirtualFile* GetVirtualFile(const char* fileName);
    static int MyLoader(lua_State * pState);

    bool Open();
    void Close();

    void GC();
    int GCBitCount();
    void* Allocate(void *ptr, size_t osize, size_t nsize);

    void AddLoader();
    void PrintGCCount(const char* what = nullptr);
    void PrintError() const;
    void PrintSnapshot() const;
    void PrintDebugRegistry() const;
    void PrintTop() const;
    void PrintTable(const Ptr<LuaTable>& table, const char* tag = nullptr) const;

    bool DoString(const char* str, const char* chunkName = nullptr)const;

    bool DoFile(const char* filename, const char* content = nullptr);
    Ptr<LuaTable> Require(const char* filename, const char* content = nullptr);
    Ptr<LuaTable> GetGlobalTable(const char* name);
    Ptr<Function> GetFunction(const char* name);
    void UnloadModule(const char* moduleName);

    ModuleManager& GetModuleManager();
  private:
    bool InitState();
    void TryAddFile(const char* filename, const char* content);
    void ClearStack();
  public:
    const string kFileExtension = ".lua";
    static const int kRetSucess = 0;
  private:
    lua_State* state_;
    Allocater* allocater_;
    ModuleManager module_manager_;
    static map<string, VirtualFile*> files_;
};
};
