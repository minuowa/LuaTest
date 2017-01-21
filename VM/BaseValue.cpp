#include "stdafx.h"
#include "BaseValue.h"
#include "LuaTable.h"
#include "Function.h"
#include "VirtualMachine.h"
#include "lstate.h"

namespace Lua {

BaseValue::BaseValue(lua_State* state, int reference)
    : state_(state)
    , lua_reference_(reference) {

}

BaseValue::~BaseValue() {
    VirtualMachine* vm = getVirtualMachine(state_);
    vm->PrintGCCount("UrefB");
    lua_unref(state_, lua_reference_);
    vm->Unref(lua_reference_);
    vm->GC();
    vm->PrintGCCount("Uref");
}

lua_State* BaseValue::GetState() const {
    return state_;
}

void BaseValue::_setkeyvalue(const char* key) {
    lua_setfield(state_, -stack_count_, key);
}

void BaseValue::_pushself() {
    lua_rawgeti(state_, LUA_REGISTRYINDEX, lua_reference_);
    stack_count_++;
}

void BaseValue::_getkey(const char* name) {
    lua_getfield(state_, -stack_count_, name);
}


void BaseValue::_pushvalue(lua_Number value) {
    lua_pushnumber(state_, value);
    stack_count_++;
}

void BaseValue::_pushvalue(const char* value) {
    lua_pushstring(state_, value);
    stack_count_++;
}

void BaseValue::_pushvalue(Pointer<LuaTable> value) {
    if (value.Valid())
        value->_pushself();
    else {
        lua_pushnil(state_);
        stack_count_++;
    }
}


void BaseValue::_clear() {
    int count = lua_gettop(state_);
    if (count > 0) {
        lua_pop(state_, count);
    }
    assert(lua_gettop(state_) == 0);
    stack_count_ = 0;
}

int BaseValue::_type() {
    return lua_type(state_, -1);
}

Pointer<LuaTable> BaseValue::_return_table() {
    int ref = luaL_ref(state_, LUA_REGISTRYINDEX);
    LuaTable* ret = new LuaTable(state_, ref);
    return ret;
}

Pointer<Function> BaseValue::_return_function() {
    int ref = luaL_ref(state_, LUA_REGISTRYINDEX);
    Function* ret = new Function(state_, ref);
    return ret;
}

const char* BaseValue::_return_str() {
    auto ret = lua_tostring(state_, -stack_count_);
    return ret;
}

lua_Number BaseValue::_return_number() {
    auto ret = lua_tonumber(state_, -stack_count_);
    return ret;
}

void BaseValue::_set_meta() {
    lua_setmetatable(state_, -stack_count_);
    this->_clear();
}

void BaseValue::_call(int argcount, int retcount) {
    lua_call(state_, argcount, retcount);
    stack_count_ = retcount;
}

int BaseValue::stack_count_ = 0;



void BaseValue::PrintAddress() {
    this->_pushself();
    ::LuaToString(state_, -stack_count_);
    this->_clear();
}

void BaseValue::Print(const char* tag/*=nullptr*/) {
}

lua_Number BaseValue::GetNumber(const char* key) {
    this->_clear();
    this->_pushself();
    this->_getkey(key);
    assert(LUA_TNUMBER == _type());
    auto ret = _return<lua_Number>();
    this->_clear();
    return ret;
}

std::string BaseValue::GetString(const char* key) {
    this->_clear();
    this->_pushself();
    this->_getkey(key);
    assert(LUA_TSTRING == _type());
    auto ret = _return<const char*>();
    this->_clear();
    return ret;
}


Pointer<Function> BaseValue::GetFunction(const char* name) {
    this->_clear();
    this->_pushself();
    this->_getkey(name);
    Function* ret = nullptr;
    if (LUA_TFUNCTION == _type()) {
        int ref = luaL_ref(state_, LUA_REGISTRYINDEX);
        ret = new Function(state_, ref);
        this->_clear();
    }

    return ret;
}

}
