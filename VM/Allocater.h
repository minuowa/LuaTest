#pragma once
namespace Lua {

class Allocater {
  public:
    Allocater();
    ~Allocater();
  private:
    map<void*, size_t> blocks_;
    map<void*, size_t> last_snapshot;
    size_t size_;
  public:
    void* Allocate(void *ptr, size_t osize, size_t nsize);
    void Snapshot();
    void DumpDifference(ostream& stream = std::cout);
  private:
    void Remove(void* ptr, bool destroy);
};
}
