#include "stdafx.h"
#include "BaseValue.h"
#include "LuaTable.h"

namespace Lua {

BaseValue::BaseValue(lua_State* state, int reference)
    : reference_(0)
    , state_(state)
    , lua_reference_(reference) {

}

BaseValue::~BaseValue() {
    assert(reference_ == 0);
    lua_unref(state_, lua_reference_);
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

void BaseValue::_pushvalue(Ptr<LuaTable> value) {
    if (value.Valid())
        value->_pushself();
    else {
        lua_pushnil(state_);
        stack_count_++;
    }
}


void BaseValue::_clear() {
    lua_pop(state_, lua_gettop(state_));
    assert(lua_gettop(state_) == 0);
    stack_count_ = 0;
}

int BaseValue::_type() {
    return lua_type(state_, -1);
}

void BaseValue::_set_meta() {
    lua_setmetatable(state_, -stack_count_);
    this->_clear();
}

int BaseValue::stack_count_ = 0;

const int BaseValue::GetReferenceCount() const {
    return reference_;
}

int BaseValue::DecReference() {
    return --reference_;
}

int BaseValue::AddReference() {
    return ++reference_;
}


void BaseValue::PrintAddress() {
    this->_pushself();
    ::LuaToString(state_, -stack_count_);
    this->_clear();
}

void BaseValue::Print(const char* tag/*=nullptr*/) {
}

lua_Number BaseValue::GetNumber(const char* key) {
    this->_pushself();
    this->_getkey(key);
    assert(LUA_TNUMBER == _type());
    auto ret = _return<lua_Number>();
    this->_clear();
    return ret;
}

std::string BaseValue::GetString(const char* key) {
    this->_pushself();
    this->_getkey(key);
    assert(LUA_TSTRING == _type());
    auto ret = _return<const char*>();
    this->_clear();
    return ret;
}
}
