#include "stdafx.h"
#include "Component.h"
#include "VirtualMachine.h"
#include "FunctionTaker.h"

namespace Lua {

Component::Component()
    : luainstance_(nullptr)
    , virtual_machine(nullptr)
    , function_taker(nullptr) {
    virtual_machine->GetComponentManager().Add(this);
}


Component::~Component() {
    this->OnDestroy();
    assert(!luainstance_.Valid());
    virtual_machine->GetComponentManager().Remove(this);
}

const Pointer<LuaTable>& Component::GetLuaInstance() const {
    return luainstance_;
}

bool Component::Initialize() {
    luainstance_ = virtual_machine->GetModuleManager().CreateInstance(filename.c_str());
    function_taker = virtual_machine->GetModuleManager().GetFunctionTaker(filename.c_str());
    return luainstance_.Valid();
}

void Component::Awake() {
    function_taker->Awake.Call(luainstance_);
}

void Component::Update() {
    function_taker->Update.Call(luainstance_);
}

void Component::OnDestroy() {
    if (!luainstance_.Valid())
        return;
    function_taker->OnDestroy.Call(luainstance_);
    virtual_machine->GetModuleManager().ReleaseInstance(this->filename.c_str(), luainstance_);
    luainstance_.RemoveReference();
}
}
