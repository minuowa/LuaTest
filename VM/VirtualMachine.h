#pragma once
#include "LuaTable.h"
#include "Pointer.h"
#include "VirtualFile.h"
#include "ModuleManager.h"
#include "Component.h"
#include "Function.h"
#include "LuaObjectManager.h"
#include "LuaModule.h"

namespace Lua {
class Allocater;
class VirtualMachine {
  public:
    VirtualMachine();
    ~VirtualMachine();
  public:
    lua_State* GetState();
    VirtualFile* GetVirtualFile(const char* fileName);
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
    void PrintTable(const Pointer<LuaTable>& table, const char* tag = nullptr) const;

    bool DoString(const char* str, const char* chunkName = nullptr)const;

    bool DoFile(const char* filename, const char* content = nullptr);
    Pointer<LuaModule> Require(const char* filename, const char* content = nullptr);
    Pointer<LuaTable> GetGlobalTable(const char* name);
    Pointer<LuaModule> GetModule(const char* name);
    Pointer<Function> GetFunction(const char* name);
    void UnloadModule(const char* moduleName);

    void Unref(int reference);

    ModuleManager& GetModuleManager();
    LuaObjectManager& GetComponentManager();
    void DumpGC(ostream& stream = std::cout);
  private:
    bool InitState();
    void TryAddFile(const char* filename, const char* content);
    void ClearStack();
    void SnapGCObjects();
  public:
    const string kFileExtension = ".lua";
    static const int kRetSucess = 0;
  private:
    lua_State* state_;
    Allocater* allocater_;
    ModuleManager module_manager_;
    LuaObjectManager component_manager_;
    map<string, VirtualFile*> files_;
    list<void*> white_objects_;

};
inline VirtualMachine* getVirtualMachine(lua_State* state) {
    return (VirtualMachine*)(state->l_G->ud);
}
};
