#include "stdafx.h"
#include "Allocater.h"
#include <memory>
namespace Lua {

Allocater::Allocater()
    : size_(0) {
}


Allocater::~Allocater() {
    assert(size_ == 0);
}

void* Allocater::Allocate(void *ptr, size_t osize, size_t nsize) {
    if (nsize == 0) {
        this->Remove(ptr, true);
        return nullptr;
    } else {
        if (ptr != nullptr)
            this->Remove(ptr, false);

        void* p = realloc(ptr, nsize);
        blocks_.insert(make_pair(p, nsize));
        size_ += nsize;
        return p;
    }
}

void Allocater::Remove(void* ptr, bool destroy) {
    auto iter = blocks_.find(ptr);
    if (iter != blocks_.end()) {
        size_ -= iter->second;
        blocks_.erase(iter);
        if (destroy)
            free(ptr);
        ptr = nullptr;
    }
}
}
