#ifndef ITEST_H
#define ITEST_H

#include "testcore/global.h"

namespace testcore {

class TEST_CORE_EXPORT ITest {
public:
    ITest() = default;
    virtual ~ITest() = default;

    virtual void test() = 0;
};

// Out-of-line definition to ensure vtable is emitted in shared library
inline ITest::~ITest() {}

}
#endif // ITEST_H
