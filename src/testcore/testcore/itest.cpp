//#
//# Copyright (C) 2020-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "testcore/itest.h"

namespace testcore {

// Non-inline out-of-line definition of the destructor.
// This makes ~ITest the "key function" of ITest, so the vtable of ITest
// is emitted (and exported) in the testcore shared library.
// Without a key function the vtable is only emitted weakly, which the
// MinGW/Windows toolchain cannot import from a DLL, resulting in:
//   undefined reference to `__imp__ZTVN8testcore5ITestE'
ITest::~ITest() {}

}
