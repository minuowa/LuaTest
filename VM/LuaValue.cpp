#include "stdafx.h"
#include "LuaValue.h"
#include "LuaTable.h"


LuaValue::LuaValue(lua_State* state, int reference)
    : reference_(0)
    , state_(state)
    , lua_reference_(reference) {

}

LuaValue::~LuaValue() {
    assert(reference_ == 0);
    lua_unref(state_, lua_reference_);
}

lua_State* LuaValue::GetState() const {
    return state_;
}

void LuaValue::_setkeyvalue(const char* key) {
    lua_setfield(state_, -stack_count_, key);
}

void LuaValue::_pushself() {
    lua_rawgeti(state_, LUA_REGISTRYINDEX, lua_reference_);
    stack_count_++;
}

void LuaValue::_getkey(const char* name) {
    lua_getfield(state_, -stack_count_, name);
}


void LuaValue::_pushvalue(lua_Number value) {
    lua_pushnumber(state_, value);
    stack_count_++;
}

void LuaValue::_pushvalue(const char* value) {
    lua_pushstring(state_, value);
    stack_count_++;
}

void LuaValue::_pushvalue(Ptr<LuaTable> value) {
    if (value.Valid())
        value->_pushself();
    else {
        lua_pushnil(state_);
        stack_count_++;
    }
}


void LuaValue::_clear() {
    lua_pop(state_, lua_gettop(state_));
    assert(lua_gettop(state_) == 0);
    stack_count_ = 0;
}

int LuaValue::_type() {
    return lua_type(state_, -1);
}

void LuaValue::_set_meta() {
    lua_setmetatable(state_, -stack_count_);
    this->_clear();
}

int LuaValue::stack_count_ = 0;

const int LuaValue::GetReferenceCount() const {
    return reference_;
}

int LuaValue::DecReference() {
    return --reference_;
}

int LuaValue::AddReference() {
    return ++reference_;
}


void LuaValue::PrintAddress() {
    this->_pushself();
    ::PrintLuaValue(state_, -stack_count_);
    this->_clear();
}

void LuaValue::Print() {
}

lua_Number LuaValue::GetNumber(const char* key) {
    this->_pushself();
    this->_getkey(key);
    assert(LUA_TNUMBER == _type());
    auto ret = _return<lua_Number>();
    this->_clear();
    return ret;
}

std::string LuaValue::GetString(const char* key) {
    this->_pushself();
    this->_getkey(key);
    assert(LUA_TSTRING == _type());
    auto ret = _return<const char*>();
    this->_clear();
    return ret;
}
