#pragma once
namespace Lua {
class Component;
class LuaObjectManager {
  public:
    LuaObjectManager();
    ~LuaObjectManager();

    void Add(Component* com);
    void Remove(Component* com);

    void Destroy();

  private:
    list<Component*> components_;
};
}


