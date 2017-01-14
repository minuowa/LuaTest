#include "stdafx.h"
#include "LuaComponent.h"
#include "VirtualMachine.h"


LuaComponent::LuaComponent()
    : luainstance_(nullptr)
    , virtual_machine(nullptr) {
}

LuaComponent::~LuaComponent() {
}

const Ptr<LuaTable>& LuaComponent::GetLuaInstance() const {
    return luainstance_;
}

bool LuaComponent::Initialize() {
    luainstance_ = virtual_machine->GetModuleManager().CreateInstance(filename.c_str());
    return luainstance_.Valid();
}

void LuaComponent::Awake() {
}

void LuaComponent::Update() {
}

void LuaComponent::OnDestroy() {
    if (!luainstance_.Valid())
        return;
    virtual_machine->GetModuleManager().ReleaseInstance(this);
}
