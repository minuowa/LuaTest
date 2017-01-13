#pragma once
class LuaValue {
  public:
    LuaValue(lua_State* state, int reference);
    ~LuaValue();
  public:
    void Push();
    int GetReferenceCount();
    int DecReference();
    int AddReference();
    lua_Number GetNumber(const char* name);
    string GetString(const char* name);

  protected:
    void GetField(const char* name);

  private:
    int mReference;
    int mLuaReference;
    lua_State* mState;
};

