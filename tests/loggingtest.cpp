#include <QTest>

#include "Logger.h"

using namespace TYA;

class LoggingTest : public QObject
{
    Q_OBJECT

private slots:
    void test1();
};

void LoggingTest::test1(){
    Logger::setLogLevel(LogLevel::Trace);

    Logger logger = Logger::get("console");

    TRACE(logger, "hoge hoge");
    DEBUG(logger, "hoge hoge");
    INFO(logger, "hoge hoge");
    WARN(logger, "hoge hoge");
    ERROR(logger, "hoge hoge");
    CRITICAL(logger, "hoge hoge");

    logger.flush();
}

QTEST_APPLESS_MAIN(LoggingTest)

#include "loggingtest.moc"
