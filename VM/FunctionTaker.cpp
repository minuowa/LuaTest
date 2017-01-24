#include "stdafx.h"
#include "FunctionTaker.h"
#include "Function.h"
#include "ModuleWrapper.h"
#include "LuaTable.h"
#include "LuaModule.h"

namespace Lua {

FunctionTaker::FunctionTaker() {
}


FunctionTaker::~FunctionTaker() {
}

bool FunctionTaker::Initialize(Pointer<LuaModule> module) {
    this->Awake = module->GetFunction("Awake");
    this->Start = module->GetFunction("Start");
    this->Update = module->GetFunction("Update");
    this->OnDestroy = module->GetFunction("OnDestroy");
    return true;
}



void FunctionTaker::Destroy() {
    this->Awake.ClearReference();
    this->Start.ClearReference();
    this->Update.ClearReference();
    this->OnDestroy.ClearReference();
}

}
