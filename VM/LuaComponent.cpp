#include "stdafx.h"
#include "LuaComponent.h"
#include "VirtualMachine.h"


LuaComponent::LuaComponent()
    : luainstance_(nullptr) {
}


LuaComponent::~LuaComponent() {
    this->OnDestroy();
}

Ptr<LuaTable>& LuaComponent::GetLuaInstance() {
    return luainstance_;
}

bool LuaComponent::Initialize() {
    luainstance_ = VirtualMachine::Instance->GetModuleManager().CreateInstance(filename.c_str());
    return luainstance_.Valid();
}

void LuaComponent::Awake() {

}

void LuaComponent::Update() {

}

void LuaComponent::OnDestroy() {
    if (!luainstance_.Valid())
        return;
    VirtualMachine::Instance->GetModuleManager().ReleaseInstance(this);
    luainstance_->DecReference();
}
