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
}
#endif // ITEST_H
