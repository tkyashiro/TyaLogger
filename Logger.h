#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <memory>

#include <spdlog/common.h>

#include "TyaLoggerExport.h"

namespace spdlog {
class logger;
}

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

#define TYA_TRACE(logger, message, ...)    (logger).trace(__FILE__, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define TYA_DEBUG(logger, message, ...)    (logger).debug(__FILE__, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define TYA_INFO(logger, message, ...)     (logger).info(__FILE__, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define TYA_WARN(logger, message, ...)     (logger).warn(__FILE__, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define TYA_ERROR(logger, message, ...)    (logger).error(__FILE__, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define TYA_CRITICAL(logger, message, ...) (logger).critical(__FILE__, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)

class TYA_LOGGER_EXPORT Logger
{
public:
    /**
     * @brief Logger this will create a instance which keeps the instance of the std::shared_ptr<spd::logger>
     * hence, although this create a new instance, the instance will serve as a shared object!
     */
    Logger();

    static void setLogLevel(LogLevel l);
    static void setLogFilePath(const std::string &path);

    void trace(const char *file, const char *func, uint32_t line, const char *message);
    void debug(const char *file, const char *func, uint32_t line, const char *message);
    void info(const char *file, const char *func, uint32_t line, const char *message);
    void warn(const char *file, const char *func, uint32_t line, const char *message);
    void error(const char *file, const char *func, uint32_t line, const char *message);
    void critical(const char *file, const char *func, uint32_t line, const char *message);

    template <typename... Args> void trace(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args);
    template <typename... Args> void debug(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args);
    template <typename... Args> void info(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args);
    template <typename... Args> void warn(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args);
    template <typename... Args> void error(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args);
    template <typename... Args> void critical(const char *file, const char *func, uint32_t line, const char *fmt, const Args... args);

    void flush();

protected:
    void log(LogLevel level, const char *file, const char *func, uint32_t line, const char *message);
    template <typename... Args> void log(LogLevel level, const char *file, const char *func, uint32_t line, const char* fmt, const Args&... args);

private:
    std::shared_ptr<spdlog::logger> logger_;

    static std::string theLogFilePath_;

private:

    static spdlog::level::level_enum map(LogLevel l);
    std::string format(const char *file, const char *func, uint32_t line, const char *message);
};

}

#include "Logger.hpp"

#endif
