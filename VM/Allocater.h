#pragma once
namespace Lua {

class Allocater {
  public:
    Allocater();
    ~Allocater();
  private:
    map<void*, size_t> blocks_;
    size_t size_;
  public:
    void* Allocate(void *ptr, size_t osize, size_t nsize);
  private:
    void Remove(void* ptr, bool destroy);
};
}
