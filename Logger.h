#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <memory>

namespace TYA {

enum class LogLevel
{
    Trace = 0x01,
    Debug = 0x02,
    Info  = 0x04,
    Warn  = 0x08,
    Error = 0x10,
    Critical = 0x20,
};

#define TRACE(logger, message) \
    logger.trace(__FILE__, __PRETTY_FUNCTION__, __LINE__, message)

#define DEBUG(logger, message) \
    logger.debug(__FILE__, __PRETTY_FUNCTION__, __LINE__, message)

#define INFO(logger, message) \
    logger.info(__FILE__, __PRETTY_FUNCTION__, __LINE__, message)

#define WARN(logger, message) \
    logger.warn(__FILE__, __PRETTY_FUNCTION__, __LINE__, message)

#define ERROR(logger, message) \
    logger.error(__FILE__, __PRETTY_FUNCTION__, __LINE__, message)

#define CRITICAL(logger, message) \
    logger.critical(__FILE__, __PRETTY_FUNCTION__, __LINE__, message)

class Logger
{
public:
    static Logger get(const std::string &name = std::string());
    static void setLogLevel(LogLevel l);

    inline void trace(const char *file, const char *func, uint32_t line, const char *message)
    {
        log(LogLevel::Trace, file, func, line, message);
    }

    inline void debug(const char *file, const char *func, uint32_t line, const char *message)
    {
        log(LogLevel::Debug, file, func, line, message);
    }

    inline void info(const char *file, const char *func, uint32_t line, const char *message)
    {
        log(LogLevel::Info, file, func, line, message);
    }

    inline void warn(const char *file, const char *func, uint32_t line, const char *message)
    {
        log(LogLevel::Warn, file, func, line, message);
    }

    inline void error(const char *file, const char *func, uint32_t line, const char *message)
    {
        log(LogLevel::Error, file, func, line, message);
    }

    inline void critical(const char *file, const char *func, uint32_t line, const char *message)
    {
        log(LogLevel::Critical, file, func, line, message);
    }

    void log(LogLevel level, const char *file, const char *func, uint32_t line, const char *message);

    void flush();

private:
    Logger(const std::string &name = std::string());
private:
    class Impl;
    std::shared_ptr<Impl> impl_;
};

}


#endif
