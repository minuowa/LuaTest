#pragma once
namespace Lua {
class Component;
class ComponentManager {
  public:
    ComponentManager();
    ~ComponentManager();

    void Add(Component* com);
    void Remove(Component* com);

    void Destroy();

  private:
    list<Component*> components_;
};
}


