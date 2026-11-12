//#
//# Copyright (C) 2027 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <QtTest>
#include "exampletest.h"

// Use this macro to initialize your own test classes.
// Check the example test.
#define TestCase(name, testClass) \
    void name() { \
        initTest(new testClass()); \
    }

/**
 * @brief The tstMain class - this is main test class
 */
class tstMain : public QObject
{
    Q_OBJECT


public:
    tstMain();

    ~tstMain();

private slots:


    // BEGIN TESTS CASES
    TestCase(exampleTest, ExampleTest)
    // END TEST CASES

private:

    /**
     * @brief initTest This method prepares @a test to run in the QApplication loop.
     * @param test are input test case class.
     */
        void initTest(testcore::ITest* test);

    QCoreApplication *_app = nullptr;
};

/**
 * @brief tstMain::tstMain
 * init all available units for testing
 */
tstMain::tstMain() {

    // init example unit test
    int argc =0;
    char * argv[] = {nullptr};

    _app = new QCoreApplication(argc, argv);
    QCoreApplication::setApplicationName("testQtSDL");
    QCoreApplication::setOrganizationName("QuasarApp");

    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QDir(path).removeRecursively();

}

tstMain::~tstMain() {
    _app->exit(0);
    delete _app;
}

void tstMain::initTest(testcore::ITest *test) {
    QTimer::singleShot(0, this, [this, test]() {
        test->test();
        delete test;
        _app->exit(0);
    });

    _app->exec();
}

QTEST_APPLESS_MAIN(tstMain)

#include "tstMain.moc"
