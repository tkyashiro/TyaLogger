#include <QTest>

#include "Logger.h"

using namespace TYA;

class LoggingTest : public QObject
{
    Q_OBJECT

private slots:
    void testMessage();
    void testFormat();
};

void LoggingTest::testMessage(){
    Logger::setLogLevel(LogLevel::Trace);

    Logger logger;

    TYA_TRACE(logger, "hoge hoge");
    TYA_DEBUG(logger, "hoge hoge");
    TYA_INFO(logger, "hoge hoge");
    TYA_WARN(logger, "hoge hoge");
    TYA_ERROR(logger, "hoge hoge");
    TYA_CRITICAL(logger, "hoge hoge");

    logger.flush();
}

void LoggingTest::testFormat(){
    Logger::setLogLevel(LogLevel::Trace);

    Logger logger;

    TYA_TRACE(logger, "Trace {}", "formatter");
    TYA_DEBUG(logger, "Debug {}", __PRETTY_FUNCTION__);
    TYA_INFO(logger, "Info {}@{}", __FILE__, __LINE__);
    TYA_WARN(logger, "Warn {}", 666);
    TYA_ERROR(logger, "Error {}", 12.3);
    TYA_CRITICAL(logger, "Critical {}", std::string("Critical!"));

    logger.flush();
}

QTEST_APPLESS_MAIN(LoggingTest)

#include "loggingtest.moc"
