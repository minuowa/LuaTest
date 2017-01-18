#include "stdafx.h"
#include "FunctionTaker.h"
#include "Function.h"
#include "LuaModule.h"
#include "LuaTable.h"

namespace Lua {

FunctionTaker::FunctionTaker() {
}


FunctionTaker::~FunctionTaker() {
}

bool FunctionTaker::Initialize(Pointer<LuaTable> module) {
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
