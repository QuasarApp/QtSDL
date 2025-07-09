//#
//# Copyright (C) 2020-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TESTUTILS_H
#define TESTUTILS_H

#include "functional"
#include <QMetaObject>
#include "testcore/global.h"

namespace testcore {

class TEST_CORE_EXPORT TestUtils
{
public:
    TestUtils();
    virtual ~TestUtils();
    bool wait(const std::function<bool()> &forWait, int msec) const;


    bool funcPrivateConnect(const std::function<bool ()> &requestFunc,
                            const std::function<bool ()> &checkFunc,
                            const std::function<QMetaObject::Connection ()> &connectFunction) const;

    bool funcPrivateConnect(const std::function<bool ()> &requestFunc,
                            const std::function<bool ()> &checkFunc) const;

};
}
#endif // TESTUTILS_H
