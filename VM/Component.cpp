#include "stdafx.h"
#include "Component.h"
#include "VirtualMachine.h"

namespace Lua {

Component::Component()
    : luainstance_(nullptr)
    , virtual_machine(nullptr) {
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
    return luainstance_.Valid();
}

void Component::Awake() {
}

void Component::Update() {
}

void Component::OnDestroy() {
    if (!luainstance_.Valid())
        return;
    virtual_machine->GetModuleManager().ReleaseInstance(this);
    luainstance_.RemoveReference();
}
}
