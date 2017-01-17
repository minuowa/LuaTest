#include "stdafx.h"
#include "PointerBase.h"


PointerBase::PointerBase()
    : reference_(0) {
}


PointerBase::~PointerBase() {
    assert(reference_ == 0);
}

const int PointerBase::GetReferenceCount() const {
    return reference_;
}

int PointerBase::DecReference() {
    return --reference_;
}

int PointerBase::AddReference() {
    return ++reference_;
}

