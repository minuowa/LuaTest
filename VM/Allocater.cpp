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


void Allocater::Snapshot() {
    last_snapshot = blocks_;
}

void Allocater::DumpDifference(ostream& stream /*= std::cout*/) {
    char buffer[128] = { 0, };
    for (auto block : blocks_) {
        if (last_snapshot.find(block.first) == last_snapshot.end()) {
            sprintf_s(buffer, "\nADDR:0X%08X,Size:%d", block.first, block.second);
            stream << buffer;
        }
    }
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
