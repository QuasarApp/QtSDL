//#
//# Copyright (C) 2020-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef EXAMPLE_TEST_H
#define EXAMPLE_TEST_H

#include <testcore/itest.h>
#include "testcore/testutils.h"

#include <QtTest>

class ExampleTest: public testcore::ITest, protected testcore::TestUtils
{
public:
    ExampleTest();
    ~ExampleTest();

    void test();

};

#endif // EXAMPLE_TEST_H
