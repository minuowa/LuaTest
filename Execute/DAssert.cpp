#include "stdafx.h"
#include "DAssert.h"



void Assert::IsTrue(bool b) {
    assert(b);
}

void Assert::IsFalse(bool b) {
    assert(!b);
}

